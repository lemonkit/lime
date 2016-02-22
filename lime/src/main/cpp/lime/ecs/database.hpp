/**
 *
 * @file     database
 * @brief    Copyright (C) 2016  author All Rights Reserved
 * @author   author
 * @date     2016/02/22
 */
#ifndef LIME_ECS_DATABASE_HPP
#define LIME_ECS_DATABASE_HPP

#include <vector>
#include <type_traits>
#include <system_error>
#include <unordered_map>
#include <unordered_set>

#include <lemon/uuid.hpp>
#include <lemon/nocopy.hpp>


namespace lime{
	namespace ecs{

		using uuid = lemon::uuids::uuid;

		class entity;
		class component;

		class database;
		
		class column
		{
		public:
			using F = void(*)(void * buff);
			virtual ~column();
			column(database &db,const uuid & id,std::size_t nsize,F createf,F closef);
		public:

			component* create();

			void set(component* com, std::error_code & ec);

			component* get(const uuid & id);
			
			component* remove(const uuid & id);

		public:

			const uuid & id() const { return _id; }

			void collect();

			const std::unordered_map<uuid, component*> & rows() const
			{
				return _rows;
			}

		private:

			database									&_db;

			uuid										_id;
			
			std::size_t									_size;

			F											_createf;

			F											_closef;
			
			std::unordered_map<uuid, component*>		_rows;
			
			std::unordered_set<component*>				_cached;
		};


		template<typename T>
		struct column_maker 
		{

			~column_maker()
			{
				static_assert(std::is_convertible<T *, component*>::value, "T must convertible to  lime::ecs::component");
			}

			static void createf(void * buff)
			{
				new(buff)T();
			}


			static void closef(void * buff)
			{
				((T*)buff)->~T();

				buff = nullptr;
			}

			static column* make(database &db, const uuid & id)
			{
				return new column(db,id,sizeof(T),createf, closef);
			}
		};



		class database : private lemon::nocopy
		{
		public:
			database();
			~database();
			
			static uuid newid()
			{

				static lemon::uuids::random_generator gen;

				return gen();
			}

		public:
			
			entity& create()
			{
				return create(newid());
			}

			entity& create(const uuid & entityid);

			entity& get(const uuid & entityid) const;

			bool has(const uuid & entityid) const;

		public:

			void collect();

			void create_column(column * cln);


			template<typename T>
			void create_column(const uuid & id)
			{
				create_column(column_maker<T>::make(*this, id));
			}

			const std::unordered_map<uuid, column*>& colunms() const
			{
				return _columns;
			}
			

		protected:

			friend class entity;

			void close(entity * obj);

			component* create_component(const uuid & comid);

			void set(component* com,std::error_code & ec);

			component* get(const uuid & entityid,const uuid & comid, std::error_code & ec) const;
			
			component* remove(const uuid & entityid, const uuid & comid, std::error_code & ec);
		
		private:
			std::unordered_map<uuid, entity*>		_rows;
			std::unordered_map<uuid, column*>		_columns;
			std::unordered_set<entity*>				_cached;
		};
	}
}

#endif //LIME_ECS_DATABASE_HPP