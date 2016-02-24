/**
 *
 * @file     object
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_OBJECT_HPP
#define LIME_ODB_OBJECT_HPP

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
			}

			/*
			 * reset object
			 */
			void reset();

			void mark(bool flag)
			{
				_marked = flag;
			}

			bool mark() const
			{
				return _marked;
			}

		public:

			/**
			 * get object id
			 */
			const oid & id() const
			{
				return _id;
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

			void attach(table* t)
			{
				_table = t;
			}

			void detach(table *t)
			{
				if(_table == t)
				{
					_table = nullptr;
				}
			}

			table * get_table() const
			{
				return _table;
			}

			
			
		private:
			database						&_db;
			oid								_id;
			std::vector<object_property*>	_properties;
			table							*_table;
			bool							_marked;
		};
	}
}

#endif //LIME_ODB_OBJECT_HPP