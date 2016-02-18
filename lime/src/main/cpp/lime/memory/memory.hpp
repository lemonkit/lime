#ifndef LIME_MEMORY_MEMORY_HPP
#define LIME_MEMORY_MEMORY_HPP

#include <unordered_map>

namespace lime {
	namespace memory{

		// the object ref id type
		using ref_t = uintptr_t;

		template<typename T>
		class object_holder
		{
		public:
			object_holder(T *t,ref_t id):_t(t),_id(id)
			{}

			T* ptr() const
			{
				return *_t;
			}

			ref_t id() const
			{
				_id;
			}

			void attach()
			{
				_id++;
			}

			void detach()
			{
				_id--;
			}

		private:
			T		*_t;
			ref_t	_id;
		};



	}
}

#endif //LIME_MEMORY_MEMORY_HPP
