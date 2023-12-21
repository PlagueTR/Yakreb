#include "yakrebpch.h"
#include "Memory.h"

namespace Yakreb {

	void Allocator::Init() {
		if (Allocator::s_Data)
			return;
		Allocator::s_Initializing = true;
		AllocatorData* data = static_cast<AllocatorData*>(Allocator::AllocateRaw(sizeof(AllocatorData)));
		new(data) AllocatorData();
		Allocator::s_Data = data;
		Allocator::s_Initializing = false;
	}

	void* Allocator::AllocateRaw(size_t size) {
		return malloc(size);
	}

	void* Allocator::Allocate(size_t size) {
		if (Allocator::s_Initializing)
			return AllocateRaw(size);
		if (!Allocator::s_Data)
			Init();
		void* memory = malloc(size);
		if (Allocator::s_Data) {
			std::scoped_lock<std::mutex> lock(Allocator::s_Data->m_Mutex);
			Allocation& alloc = Allocator::s_Data->m_AllocationMap[memory];
			alloc.Memory = memory;
			alloc.Size = size;

			Allocator::s_GlobalStats.TotalAllocated += size;
		}
		return memory;
	}

	void* Allocator::Allocate(size_t size, const char* desc) {
		if (!Allocator::s_Data)
			Init();
		void* memory = malloc(size);
		if (Allocator::s_Data) {
			std::scoped_lock<std::mutex> lock(Allocator::s_Data->m_Mutex);
			Allocation& alloc = Allocator::s_Data->m_AllocationMap[memory];
			alloc.Memory = memory;
			alloc.Size = size;
			alloc.Category = desc;

			Allocator::s_GlobalStats.TotalAllocated += size;
			if (desc) {
				Allocator::s_Data->m_AllocationStatsMap[desc].TotalAllocated += size;
				Allocator::s_Data->m_AllocationStatsMap[desc].Instances++;
			}
		}
		return memory;
	}

	void Allocator::Free(void* memory) {
		if (memory == nullptr)
			return;
		{
			bool found = false;
			{
				std::scoped_lock<std::mutex> lock(Allocator::s_Data->m_Mutex);
			    detail::Memory::AllocationMap::iterator allocMapIt = Allocator::s_Data->m_AllocationMap.find(memory);
				found = allocMapIt != Allocator::s_Data->m_AllocationMap.end();
				if (found) {
					const Allocation& alloc = allocMapIt->second;
					Allocator::s_GlobalStats.TotalFreed += alloc.Size;
					if (alloc.Category) {
						s_Data->m_AllocationStatsMap[alloc.Category].TotalFreed += alloc.Size;
						s_Data->m_AllocationStatsMap[alloc.Category].Instances--;
					}
					s_Data->m_AllocationMap.erase(memory);
				}
			}
			if (!found)
				YGE_CORE_WARN("Memory block \"{}\" not present in allocation map!", memory);
		}
		free(memory);
	}

	const AllocationStatsVec Allocator::GetAllocationStatsVec() {
		std::scoped_lock<std::mutex> lock(Allocator::s_Data->m_Mutex);
		AllocationStatsVec allocationVec(Allocator::s_Data->m_AllocationStatsMap.begin(), Allocator::s_Data->m_AllocationStatsMap.end());
		std::sort(allocationVec.rbegin(), allocationVec.rend(),
			[](std::pair<const char*, InstanceAllocationStats>& lhs, std::pair<const char*, InstanceAllocationStats>& rhs) {
				InstanceAllocationStats& lhsStats = lhs.second;
				InstanceAllocationStats& rhsStats = rhs.second;
				return (lhsStats.TotalAllocated - lhsStats.TotalFreed) < (rhsStats.TotalAllocated - rhsStats.TotalFreed);
			});
		return allocationVec;
	}

}

#ifdef YGE_TRACK_MEMORY
	#ifdef YGE_COMPILER_MSVC

		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new(size_t size) {
			return Yakreb::Allocator::Allocate(size);
		}

		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new[](size_t size) {
			return Yakreb::Allocator::Allocate(size);
		}

		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new(size_t size, const char* desc) {
			return Yakreb::Allocator::Allocate(size, desc);
		}

		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new[](size_t size, const char* desc) {
			return Yakreb::Allocator::Allocate(size, desc);
		}

		void __CRTDECL operator delete(void* memory) {
			Yakreb::Allocator::Free(memory);
		}

		void __CRTDECL operator delete[](void* memory) {
			Yakreb::Allocator::Free(memory);
		}

		void __CRTDECL operator delete(void* memory, const char* desc) {
			Yakreb::Allocator::Free(memory);
		}

		void __CRTDECL operator delete[](void* memory, const char* desc) {
			Yakreb::Allocator::Free(memory);
		}

	#elif defined(YGE_COMPILER_GCC)

		std::map<const char*, const char*> Yakreb::detail::Memory::Demangler::DemangledMap;

		_GLIBCXX_NODISCARD void* operator new(size_t size) _GLIBCXX_THROW(std::bad_alloc) {
			return Yakreb::Allocator::Allocate(size);
		}

		_GLIBCXX_NODISCARD void* operator new[](size_t size) _GLIBCXX_THROW(std::bad_alloc) {
			return Yakreb::Allocator::Allocate(size);
		}

		_GLIBCXX_NODISCARD void* operator new(size_t size, const char* desc) _GLIBCXX_THROW(std::bad_alloc) {
			return Yakreb::Allocator::Allocate(size, desc);
		}

		_GLIBCXX_NODISCARD void* operator new[](size_t size, const char* desc) _GLIBCXX_THROW(std::bad_alloc) {
			return Yakreb::Allocator::Allocate(size, desc);
		}

		void operator delete(void* memory) _GLIBCXX_USE_NOEXCEPT {
			Yakreb::Allocator::Free(memory);
		}

		void operator delete[](void* memory) _GLIBCXX_USE_NOEXCEPT {
			Yakreb::Allocator::Free(memory);
		}

		void operator delete(void* memory, const char* desc) _GLIBCXX_USE_NOEXCEPT {
			Yakreb::Allocator::Free(memory);
		}

		void operator delete[](void* memory, const char* desc) _GLIBCXX_USE_NOEXCEPT {
			Yakreb::Allocator::Free(memory);
		}

	#endif
#endif