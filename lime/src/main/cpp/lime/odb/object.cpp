#include <cassert>
#include <lime/odb/object.hpp>
#include <lime/odb/property.hpp>
#include <lime/odb/table.hpp>

namespace lime{
	namespace odb{

		object::object(database &db)
			:_db(db),_table(nullptr),_parent(nullptr)
		{
		}

		
		void object::reset()
		{
			for(auto pro : _properties)
			{
				_db.close_property(this, pro);
			}

			_properties.clear();

			_children.clear();
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

			for (auto child : _children)
			{
				t->insert(child);
			}
		}

		void object::detach(table *t)
		{
			if (_table == t)
			{
				_table = nullptr;

				_db.detach(this);
			}

			for (auto child : _children)
			{
				t->remove(child);
			}
		}

		void object::add_child(object* child,std::error_code & ec)
		{
			if(
				child->parent() ||
				get_child_by_name(child->tag(),child->_taghashcode) ||
				get_child_by_oid(child->id(),child->_idhashcode))
			{
				ec = make_error_code(errc::duplicate_add_child);
			}

			_children.push_back(child);

			if (_table)
			{
				_table->insert(child);
			}
		}

		object * object::get_child_by_name(const std::string &name, std::size_t hashcode)
		{
			if(name.empty())
			{
				return nullptr;
			}

			for(auto child : _children)
			{
				if(child->_taghashcode == hashcode && child->tag() == name)
				{
					return child;
				}
			}

			return nullptr;
		}

		object * object::get_child_by_oid(const oid &id,std::size_t hashcode)
		{
			for (auto child : _children)
			{
				if (child->_idhashcode == hashcode && child->id() == id)
				{
					return child;
				}
			}

			return nullptr;
		}

		void object::remove_child(object *child)
		{
			for (auto iter = _children.begin(); iter != _children.end(); iter ++)
			{
				if((*iter)->_idhashcode == child->_idhashcode &&  (*iter)->_id == child->_id)
				{
					_children.erase(iter);

					child->_parent = nullptr;

					if(_table)
					{
						_table->remove(child);
					}

					break;
				}
			}
		}
	}
}