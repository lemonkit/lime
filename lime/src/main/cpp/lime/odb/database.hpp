/**
 *
 * @file     database
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_DATABASE_HPP
#define LIME_ODB_DATABASE_HPP
#include <vector>
#include <string>
#include <cstddef>
#include <type_traits>
#include <system_error>
#include <unordered_set>
#include <unordered_map>


#include <lemon/uuid.hpp>
#include <lemon/nocopy.hpp>
#include <lime/odb/odb_errors.hpp>

namespace lime{
	namespace odb{

		class object;
		class object_property;
		

		using oid = lemon::uuids::uuid;


		class table;
		class column;
		class indexer;

		template<typename T>
		struct column_creator
		{
			static void createf(void * buff)
			{
				new(buff) T();
			}

			static void deletef(void *buff)
			{
				((T*)buff)->~T();
				buff = nullptr;
			}
		};

		/**
		 * game object memory database
		 */
		class database final: private lemon::nocopy
		{
		public:
			static oid newoid()
			{
				static lemon::uuids::random_generator g;

				return g();
			}
		public:
			
			database();
			
			~database();
		
			/**
			 * create new object by oid
			 */
			object *create(const oid &id,std::error_code & ec) noexcept;

			/**
			 * create new object with random oid
			 */
			object *create(std::error_code & ec) noexcept
			{

				return create(newoid(),ec);
			}

			/**
			 * create new object by oid
			 */
			object *create(const oid &id)
			{
				std::error_code ec;
				auto obj = create(id,ec);
				if (ec)
				{
					throw std::system_error(ec, "odb create new object error");
				}

				return obj;
			}

			/**
			 * create new object using random oid
			 */
			object *create()
			{
				return create(newoid());
			}

		public:

			template<typename T>
			void register_column(const oid &id)
			{
				typedef column_creator<T> creator;

				std::error_code ec;

				register_column(id, sizeof(T), creator::createf, creator::deletef,ec);

				if(ec)
				{
					throw std::system_error(ec);
				}
			}

			template<typename T>
			void register_column(const oid &id,std::error_code & ec)
			{
				typedef column_creator<T> creator;

				register_column(id, sizeof(T), creator::createf, creator::deletef, ec);
			}

			table* create_table(const std::string & name, std::error_code & ec);

			table* create_table(const std::string & name)
			{
				std::error_code  ec;

				auto t = create_table(name, ec);

				if(ec)
				{
					throw std::system_error(ec);
				}

				return t;
			}

			table* get_table(const std::string & name);

		public:

			bool garbagecollect(bool flag);

		private:

			friend class object;
			friend class object_property;
			friend class table;

			void register_column(
				const oid &id,
				std::size_t nsize,
				void(*createf)(void*buff),
				void(*deletef)(void*buff),
				std::error_code & ec) noexcept;

			column * get_column_by_oid(const oid & id) noexcept;

			object_property* create_property(object* obj, const oid & id,std::error_code & ec) noexcept;

			void close_property(object* obj, object_property * pro) noexcept;

			const std::vector<column*>& columns() const
			{
				return _columns;
			}

			void attach(object *obj);
			void detach(object *obj);
			
		private:
			std::vector<column*>					_columns;	// register column array
			std::vector<table*>						_tables;	// register table list
			std::unordered_set<object*>				_weakrefs;	// cached weak reference object table
			std::vector<object*>					_cached;	// cached unused object
		};
	}
}

#endif //LIME_ODB_DATABASE_HPP