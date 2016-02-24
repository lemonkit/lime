#include <lime/odb/table.hpp>
#include <lime/odb/object.hpp>
#include <lime/odb/column.hpp>
#include <lime/odb/indexer.hpp>
#include <lime/odb/property.hpp>
#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		database::database():_gc(0)
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

			for (auto kv : _objects)
			{
				delete kv.second;
			}

			
		}

		object *database::create(const oid &id, std::error_code & ec) noexcept
		{
			if(_objects.count(id) != 0)
			{
				ec = make_error_code(errc::duplicate_object_oid);
				return nullptr;
			}

			object *obj = nullptr;

			if(_cached.empty())
			{
				obj = new object(*this);

				obj->id(id);
			}
			else
			{
				obj = *_cached.begin();

				_cached.pop_back();

				obj->id(id);
			}

			_objects[id] = obj;

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

		bool database::garbagecollect()
		{
			if(_cached.empty() || _gc == 1000)
			{
				_gc = 0;

				for(auto t :_tables)
				{
					for(auto o :t->objects())
					{
						o->mark(true);
					}
				}

				for(auto o : _objects)
				{
					if (o.second->mark())
					{
						_gc_swap[o.second->id()] = o.second;
					}
					else
					{
						o.second->reset();

						_cached.push_back(o.second);
					}
				}

				_objects.clear();

				_objects.swap(_gc_swap);

				return true;
			}

			_gc++;

			return false;
		}
	}
}