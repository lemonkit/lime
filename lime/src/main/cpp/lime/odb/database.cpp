#include <lime/odb/table.hpp>
#include <lime/odb/object.hpp>
#include <lime/odb/column.hpp>
#include <lime/odb/indexer.hpp>
#include <lime/odb/property.hpp>
#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		database::database()
		{

		}

		database::~database()
		{
			for (auto t :_tables)
			{
				delete t;
			}

			for(auto o : _cached)
			{
				delete o;
			}
		}

		object *database::create(const oid &id, std::error_code &) noexcept
		{
			object *obj = nullptr;

			if(_cached.empty())
			{
				obj = new object(*this);

				obj->id(id);
			}
			else
			{
				obj = _cached.back();

				_cached.pop_back();

				obj->id(id);
			}

			_weakrefs.insert(obj);

			return obj;
		}

		void database::register_column(
			const oid &id, 
			std::size_t nsize,
			void(*createf)(void*buff), 
			void(*deletef)(void*buff),
			std::error_code & ec) noexcept
		{
			if(get_column_by_oid(id))
			{
				ec = make_error_code(errc::duplicate_column_oid);
				return;
			}

			_columns.push_back(new column(id, nsize, createf, deletef));
		}

		column * database::get_column_by_oid(const oid & id) noexcept
		{
			std::hash<oid> hasher;

			auto hashcode = hasher(id);

			for(auto c : _columns)
			{
				if(c->hashcode() == hashcode && id == c->id())
				{
					return c;
				}
			}

			return nullptr;
		}

		object_property* database::create_property(object* obj, const oid & id, std::error_code & ec) noexcept
		{
			auto cln = get_column_by_oid(id);

			if(!cln)
			{
				ec = make_error_code(errc::unknown_column_oid);
			}

			return cln->create_property(obj);
		}

		void database::close_property(object*, object_property * pro) noexcept
		{
			pro->close();
		}

		table* database::create_table(const std::string & name, std::error_code & ec)
		{
			if(get_table(name))
			{
				ec = make_error_code(errc::duplicate_table_name);
				return nullptr;
			}

			auto t = new table(*this, name);

			_tables.push_back(t);

			return t;
		}

		table* database::get_table(const std::string & name)
		{
			std::hash<std::string> hasher;
			auto hashcode = hasher(name);
			
			for(auto t: _tables)
			{
				if(t->hashcode() == hashcode && t->name() == name)
				{
					return t;
				}
			}

			return nullptr;
		}

		int database::garbagecollect(bool flag)
		{
			if(flag || _cached.empty() || _weakrefs.size() > 100)
			{
				for(auto o : _weakrefs)
				{
					o->reset();

					_cached.push_back(o);
				}
				auto c = _weakrefs.size();
				_weakrefs.clear();

				return c;
			}

			return 0;
		}

		void database::attach(object *obj)
		{
			_weakrefs.erase(obj);
		}

		void database::detach(object *obj)
		{
			_weakrefs.insert(obj);
		}
	}
}