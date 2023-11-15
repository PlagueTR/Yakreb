#pragma once

#include "Yakreb/Core/PlatformDetection.h"
#include "Yakreb/Core/ConfigMacros.h"

#include <stdlib.h>
#include <vector>
#include <map>
#include <mutex>

#ifdef YGE_COMPILER_GCC
	#include <cxxabi.h>
#endif

namespace Yakreb {

	struct AllocationStats {
		size_t TotalAllocated = 0;
		size_t TotalFreed = 0;
	};

	struct InstanceAllocationStats {
		size_t TotalAllocated = 0;
		size_t TotalFreed = 0;
		uint32_t Instances = 0;
	};

	struct Allocation {
		void* Memory = 0;
		size_t Size = 0;
		const char* Category = 0;
	};

	template <class T>
	struct Mallocator {
		typedef T value_type;
		Mallocator() = default;

		template<class T2>
		constexpr Mallocator(const Mallocator<T2>&) noexcept {}

		T* allocate(std::size_t n) {
			if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
				throw std::bad_array_new_length();
			if (auto p = static_cast<T*>(std::malloc(n * sizeof(T))))
				return p;
			throw std::bad_alloc();
		}

		void deallocate(T* p, std::size_t n) noexcept {
			std::free(p);
		}

	};

	namespace detail::Memory {
		using MapAlloc = Mallocator<std::pair<const void* const, Allocation>>;
		using StatsMapAlloc = Mallocator<std::pair<const char* const, InstanceAllocationStats>>;
		using StatsVecAlloc = Mallocator<std::pair<const char*, InstanceAllocationStats>>;
		using AllocationMap = std::map<const void*, Allocation, std::less<const void*>, MapAlloc>;
	}

	using AllocationStatsMap = std::map<const char*, InstanceAllocationStats, std::less<const char*>, detail::Memory::StatsMapAlloc>;
	using AllocationStatsVec = std::vector<std::pair<const char*, InstanceAllocationStats>, detail::Memory::StatsVecAlloc>;

	class Allocator {
		public:

			struct AllocatorData {
				detail::Memory::AllocationMap m_AllocationMap;
				AllocationStatsMap m_AllocationStatsMap;

				std::mutex m_Mutex;
			};

			static void Init();

			static void* AllocateRaw(size_t size);

			static void* Allocate(size_t size);
			static void* Allocate(size_t size, const char* desc);

			static void Free(void* memory);

			static const AllocationStats& GetGlobalAllocationStats() { return s_GlobalStats; }
			static const AllocationStatsMap& GetAllocationStatsMap() { return s_Data->m_AllocationStatsMap; }

			// Slow, creates a copy of the map and sorts it according to current memory usage from highest to lowest
			static const AllocationStatsVec GetAllocationStatsVec();

		private:
			inline static bool s_Initializing = false;
			inline static AllocatorData* s_Data = nullptr;
			inline static AllocationStats s_GlobalStats;

	};

}

namespace Yakreb::detail::Memory {

	class Demangler {
	public:
		#ifdef YGE_COMPILER_GCC
			static std::map<const char*, const char*> DemangledMap;
		#endif

		template <typename T>
		static const char* Demangle() {
			#ifdef YGE_COMPILER_MSVC
				return typeid(T).name();
			#elif defined(YGE_COMPILER_GCC)
				const char* name = typeid(T).name();
				std::map<const char*, const char*>::iterator demangledMapIt = DemangledMap.find(name);
				bool found = demangledMapIt != DemangledMap.end();
				if (found) {
					return demangledMapIt->second;
				}
				else {
					int status;
					const char* prettyName = abi::__cxa_demangle(name, nullptr, nullptr, &status);
					if (status == 0) {
						DemangledMap[name] = prettyName;
						return prettyName;
					}
					else {
						DemangledMap[name] = name;
						return name;
					}
				}
			#endif
		}
	};

}

#ifdef YGE_TRACK_MEMORY

	#ifdef YGE_COMPILER_MSVC
		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new(size_t size);
		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new[](size_t size);
		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new(size_t size, const char* desc);
		_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR void* __CRTDECL operator new[](size_t size, const char* desc);

		void __CRTDECL operator delete(void* memory);
		void __CRTDECL operator delete[](void* memory);
		void __CRTDECL operator delete(void* memory, const char* desc);
		void __CRTDECL operator delete[](void* memory, const char* desc);
	#elif defined(YGE_COMPILER_GCC)
		_GLIBCXX_NODISCARD void* operator new(size_t size) _GLIBCXX_THROW(std::bad_alloc) __attribute__((__externally_visible__));
		_GLIBCXX_NODISCARD void* operator new[](size_t size) _GLIBCXX_THROW(std::bad_alloc) __attribute__((__externally_visible__));
		_GLIBCXX_NODISCARD void* operator new(size_t size, const char* desc) _GLIBCXX_THROW(std::bad_alloc) __attribute__((__externally_visible__));
		_GLIBCXX_NODISCARD void* operator new[](size_t size, const char* desc) _GLIBCXX_THROW(std::bad_alloc) __attribute__((__externally_visible__));

		void operator delete(void* memory) _GLIBCXX_USE_NOEXCEPT __attribute__((__externally_visible__));
		void operator delete[](void* memory) _GLIBCXX_USE_NOEXCEPT __attribute__((__externally_visible__));
		void operator delete(void* memory, const char* desc) _GLIBCXX_USE_NOEXCEPT __attribute__((__externally_visible__));
		void operator delete[](void* memory, const char* desc) _GLIBCXX_USE_NOEXCEPT __attribute__((__externally_visible__));
	#endif

	#define ygenew(desc) new(desc)

#else
	
	#define ygenew(desc) new

#endif