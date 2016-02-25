/**
 *
 * @file     table
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_TABLE_HPP
#define LIME_ODB_TABLE_HPP

#include <lime/odb/database.hpp>
#include <lime/odb/indexer.hpp>
namespace lime{
	namespace odb{
		/**
		 * odb memory table 
		 */
		class table : private lemon::nocopy
		{
		public:
			
			table(database &db,const std::string &name);
			
			~table();

			const std::string & name() const 
			{
				return _name;
			}

			std::size_t hashcode() const
			{
				return _hashcode;
			}

		public:

			const std::vector<indexer*> & indxers() const
			{
				return _indexers;
			}

			indexer * get_indexer_by_name(const std::string & name) const;

			template<typename T,typename ...Args>
			void create_indexer(const std::string name,const oid & clid, std::error_code &ec, Args && ...args)
			{
				static_assert(std::is_convertible<T*, indexer*>::value, "T must child of indexer");

				auto cln = _db.get_column_by_oid(clid);

				if(!cln)
				{
					ec = make_error_code(errc::unknown_column_oid);
					return;
				}

				auto idx = new T(*cln,name,std::forward<Args>(args)...);

				register_indexer(idx);
			}

			template<typename T, typename ...Args>
			void create_indexer(const std::string name, const oid & clid, Args && ...args)
			{
				std::error_code ec;

				create_indexer(name, clid, ec, std::forward<Args>(args)...);
			}

		public:
			void insert(object *obj) 
			{
				std::error_code ec;

				insert(obj, ec);

				if(ec)
				{
					throw std::system_error(ec);
				}
			}

			void insert(object *obj,std::error_code & ec) noexcept;

			void remove(object *obj) noexcept;

			std::unordered_set<object*> & objects() 
			{
				return _objects;
			}
			
		private:
			void register_indexer(indexer *idx);
		private:
			database						&_db;
			std::string						_name;
			std::size_t						_hashcode;
			std::vector<indexer*>			_indexers;
			std::unordered_set<object*>		_objects;
		};
	}
}
#endif //LIME_ODB_TABLE_HPP