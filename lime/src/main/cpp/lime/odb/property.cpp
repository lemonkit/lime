#include <lime/odb/column.hpp>
#include <lime/odb/property.hpp>

namespace lime{
	namespace odb{

		object_property::object_property(column & cln) noexcept
			:_column(cln)
		{

		}

		void object_property::close() noexcept
		{
			_column.close_property(this);
		}

		std::size_t object_property::hashcode() const
		{
			return _column.hashcode();
		}

		const oid & object_property::id() const
		{
			return _column.id();
		}

		void object_property::reset(object * obj) noexcept
		{
			_obj = obj;
		}
	}
}