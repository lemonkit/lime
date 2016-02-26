/**
 *
 * @file     object
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_OBJECT_HPP
#define LIME_ODB_OBJECT_HPP
#include <string>
#include <vector>
#include <lemon/nocopy.hpp>
#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		
		class object_property;

		class object : lemon::nocopy
		{
		protected:
			friend class database;

			object(database &db);

			/**
			 * set new object oid
			 */
			void id(const oid & val)
			{
				_id = val;
				std::hash<oid> hasher;

				_idhashcode = hasher(val);
			}

			/*
			 * reset object
			 */
			void reset();

		public:

			/**
			 * get object id
			 */
			const oid & id() const
			{
				return _id;
			}

			void tag(const std::string & name)
			{
				_tag = name;

				std::hash<std::string> hasher;

				_taghashcode = hasher(_tag);
			}

			const std::string & tag() const
			{
				return _tag;
			}


			object_property* add_property(const oid & id,std::error_code & ec);

			object_property* add_property(const oid & id)
			{
				std::error_code ec;

				auto pro = add_property(id, ec);

				if(ec)
				{
					throw std::system_error(ec);
				}

				return pro;
			}

			
			
			object_property* get_property(const oid & id);

			void remove_property(const oid & id);

			const std::vector<object_property*> & properties() const
			{
				return _properties;
			}

		public:

			void attach(table* t);

			void detach(table *t);

			table * get_table() const
			{
				return _table;
			}

			void add_child(object* child, std::error_code &ec);

			void add_child(object* child)
			{
				std::error_code ec;

				add_child(child, ec);

				if(ec)
				{
					throw std::system_error(ec);
				}
			}

			object * get_child(const std::string & tagname)
			{
				std::hash<std::string> hasher;

				return get_child_by_name(tagname,hasher(tagname));
			}

			object * get_child(const oid &id)
			{
				std::hash<oid> hasher;

				return get_child_by_oid(id,hasher(id));
			}

			void remove_child(object *child);

			void remove_from_parent()
			{
				if(_parent)
				{
					_parent->remove_child(this);
				}
			}

			object * parent() const
			{
				return _parent;
			}
		private:

			object * get_child_by_name(const std::string &name, std::size_t hashcode);

			object * get_child_by_oid(const oid &id,std::size_t hashcode);

		private:
			database						&_db;
			oid								_id;
			std::size_t						_idhashcode;
			std::vector<object_property*>	_properties;
			table							*_table;
			object							*_parent;
			std::vector<object*>			_children;
			std::string						_tag;
			std::size_t						_taghashcode;
		};
	}
}

#endif //LIME_ODB_OBJECT_HPP