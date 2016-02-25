#include <cassert>
#include <lime/odb/object.hpp>
#include <lime/odb/property.hpp>

namespace lime{
	namespace odb{

		object::object(database &db)
			:_db(db),_table(nullptr)
		{
		}

		
		void object::reset()
		{
			for(auto pro : _properties)
			{
				_db.close_property(this, pro);
			}

			_properties.clear();
		}

		object_property* object::add_property(const oid & id, std::error_code & ec)
		{
			if(get_property(id))
			{
				ec = make_error_code(errc::duplicate_column_oid);
				return nullptr;
			}

			auto pro = _db.create_property(this, id, ec);

			if(ec)
			{
				return nullptr;
			}

			_properties.push_back(pro);

			return pro;
		}

		object_property* object::get_property(const oid & id)
		{
			std::hash<oid> hasher;

			auto hashcode = hasher(id);

			for(auto pro : _properties)
			{
				if(pro->hashcode() == hashcode && pro->id() == id)
				{
					return pro;
				}
			}

			return nullptr;
		}

		void object::remove_property(const oid & id)
		{
			auto pro = get_property(id);

			if(pro)
			{
				_db.close_property(this, pro);
			}
		}

		void object::attach(table* t)
		{
			assert(_table == nullptr);
			_table = t;

			_db.attach(this);
		}

		void object::detach(table *t)
		{
			if (_table == t)
			{
				_table = nullptr;

				_db.attach(this);
			}
		}
	}
}