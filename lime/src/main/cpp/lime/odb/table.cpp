#include <lime/odb/table.hpp>
#include <lime/odb/object.hpp>
#include <lime/odb/column.hpp>
#include <lime/odb/indexer.hpp>
#include <lime/odb/property.hpp>

namespace lime{
	namespace odb{

		table::table(database &db, const std::string &name)
			:_db(db),_name(name)
		{
			std::hash<std::string> hasher;

			_hashcode = hasher(name);

			for(auto c :_db.columns())
			{
				_indexers.push_back(new object_indexer(*c, lemon::uuids::to_string(c->id())));
			}
		}

		table::~table()
		{
			for(auto i: _indexers)
			{
				delete i;
			}
		}

		indexer* table::get_indexer_by_name(const std::string & name) const
		{
			std::hash<std::string> hasher;
			auto hashcode = hasher(name);

			for (auto i : _indexers)
			{
				if(i->hashcode() == hashcode && i->name() == name)
				{
					return i;
				}
			}

			return nullptr;
		}

		void table::register_indexer(indexer *idx)
		{
			_indexers.push_back(idx);
		}

		void table::insert(object *obj) noexcept
		{
			auto result = _objects.insert(obj);

			if(result.second)
			{
				for(auto pro :obj->properties())
				{
					auto cln = pro->get_column();

					for(auto i : _indexers)
					{
						if(i->get_column() == cln)
						{
							i->update(pro);
						}
					}
				}
			}

			obj->attach(this);
		}

		void table::remove(object *obj) noexcept
		{
			if(_objects.erase(obj))
			{
				for (auto pro : obj->properties())
				{
					auto cln = pro->get_column();

					for (auto i : _indexers)
					{
						if (i->get_column() == cln)
						{
							i->remove(pro);
						}
					}
				}
			}

			obj->detach(this);
		}
	}
}