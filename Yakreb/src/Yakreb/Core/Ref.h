#pragma once

#include "Yakreb/Core/ConfigMacros.h"
#include "Yakreb/Core/Memory.h"

#include <stdint.h>
#include <typeinfo>

namespace Yakreb {

	class RefCounted {
		public:
			void IncRefCount() const { ++m_RefCount; }
			void DecRefCount() const { --m_RefCount; }

			uint32_t GetRefCount() const { return m_RefCount; }

		private:
			mutable uint32_t m_RefCount = 0;

	};

	template <typename T>
	class Ref {
		public:
			Ref() : m_Instance(nullptr) {}
			Ref(std::nullptr_t n) : m_Instance(nullptr) {}
			Ref(T* instance) : m_Instance(instance) {
				static_assert(std::is_base_of<RefCounted, T>::value, "Class is not RefCounted!");
				IncRef();
			}

			Ref(const Ref<T>& other) : m_Instance(other.m_Instance) {
				IncRef();
			}

			template <typename T2>
			Ref(Ref<T2>& other) {
				m_Instance = other.m_Instance;
				IncRef();
			}

			template <typename T2>
			Ref(Ref<T2>&& other) {
				m_Instance = other.m_Instance;
				other.m_Instance = nullptr;
			}

			~Ref() {
				DecRef();
			}

			Ref& operator=(std::nullptr_t) {
				DecRef();
				m_Instance = nullptr;
				return *this;
			}

			Ref& operator=(const Ref<T>& other) {
				if (this == &other)
					return *this;

				other.IncRef();
				DecRef();

				m_Instance = other.m_Instance;
				return *this;
			}

			template<typename T2>
			Ref& operator=(const Ref<T2>& other) {
				other.IncRef();
				DecRef();

				m_Instance = other.m_Instance;
				return *this;
			}

			template<typename T2>
			Ref& operator=(Ref<T2>&& other)
			{
				DecRef();

				m_Instance = other.m_Instance;
				other.m_Instance = nullptr;
				return *this;
			}

			operator bool() { return m_Instance != nullptr; }
			operator bool() const { return m_Instance != nullptr; }

			T* operator->() { return m_Instance; }
			const T* operator->() const { return m_Instance; }

			T& operator*() { return *m_Instance; }
			const T& operator*() const { return *m_Instance; }

			bool operator==(const Ref<T>& other) const {
				return m_Instance == other.m_Instance;
			}

			bool operator!=(const Ref<T>& other) const {
				return !(*this == other);
			}

			T* Raw() { return m_Instance; }
			const T* Raw() const { return m_Instance; }

			void Reset(T* instance = nullptr) {
				DecRef();
				m_Instance = instance;
			}

			template<typename T2>
			Ref<T2> As() const {
				return Ref<T2>(*this);
			}

			template<typename... Args>
			static Ref<T> Create(Args&&... args) {
				#ifdef YGE_TRACK_MEMORY
					#ifdef YGE_COMPILER_MSVC
						return Ref<T>(new(detail::Memory::Demangler::Demangle<T>()) T(std::forward<Args>(args)...));
					#elif defined(YGE_COMPILER_GCC)
						return Ref<T>(new(detail::Memory::Demangler::Demangle<T>()) T(std::forward<Args>(args)...));
					#else
						// Unsupported compilers
						return Ref<T>(new T(std::forward<Args>(args)...));
					#endif
				#else
					return Ref<T>(new T(std::forward<Args>(args)...));
				#endif
			}

		private:
			void IncRef() const {
				if (m_Instance)
					m_Instance->IncRefCount();
			}

			void DecRef() const {
				if (m_Instance) {
					m_Instance->DecRefCount();
					if (m_Instance->GetRefCount() == 0) {
						delete m_Instance;
						m_Instance = nullptr;
					}
				}
			}

			template <class T2>
			friend class Ref;
			mutable T* m_Instance;

	};

}