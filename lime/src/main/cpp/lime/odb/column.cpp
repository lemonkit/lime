#include <lime/odb/column.hpp>
#include <lime/odb/property.hpp>

namespace lime{
	namespace odb{

		column::column(
			const oid & id,
			std::size_t nsize,
			void(*createf)(void*buff),
			void(*deletef)(void*buff))
			:_createf(createf)
			,_deletef(deletef)
			,_id(id)
			,_size(nsize + sizeof(object_property))
		{
			std::hash<oid> gen;

			_hashcode = gen(id);
		}

		object_property *column::create_property(object *obj)
		{

			object_property * pro;

			if(_cached.empty())
			{
				auto buff = new char[_size];

				pro = new(buff) object_property(*this);
			}
			else
			{
				pro = _cached.back();

				_cached.pop_back();
			}

			try
			{
				_createf(pro->buff());

				pro->reset(obj);
			}
			catch (...)
			{
				_cached.push_back(pro);
				throw;
			}

			return pro;
		}

		void column::close_property(object_property* pro) noexcept
		{
			_deletef(pro->buff());

			pro->reset(nullptr);

			_cached.push_back(pro);
		}
	}
}