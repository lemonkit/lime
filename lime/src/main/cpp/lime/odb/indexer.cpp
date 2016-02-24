#include <lime/odb/object.hpp>
#include <lime/odb/indexer.hpp>
#include <lime/odb/property.hpp>

namespace lime {
	namespace odb {

		indexer::indexer(column& cln, const std::string &name) noexcept
			:_column(cln),_name(name)
		{
			std::hash<std::string> hasher;

			_hashcode = hasher(name);
		}

		void object_indexer::update(object_property *pro) 
		{
			_indexer[pro->get_object()->id()] = pro;
		}

		void object_indexer::remove(object_property *pro)
		{
			_indexer.erase(pro->id());
		}
	}
}
