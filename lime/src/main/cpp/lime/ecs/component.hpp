/**
 *
 * @file     component
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/22
 */
#ifndef LIME_ECS_COMPONENET_HPP
#define LIME_ECS_COMPONENET_HPP

#include <lemon/uuid.hpp>
#include <lemon/nocopy.hpp>
#include <lime/ecs/entity.hpp>
#include <lime/ecs/database.hpp>

namespace lime {
	namespace ecs{

		using uuid = lemon::uuids::uuid;

		class entity;
		class database;

		class component final: private lemon::nocopy
		{
		protected:
		
			friend class column;
			
			component(database & db, const uuid & id)
				:_db(db),_id(id),_entity(nullptr)
			{}

			virtual ~component(){}

			void *buff()
			{
				return _buff;
			}

		public:

			database & db() { return _db; }

			const uuid & id() const { return _id; }

			void attach(entity * obj);

			entity* detach();

			const uuid& entity_id() const
			{
				return _entity->id();
			}
			
			bool attached() const 
			{
				return _entity != nullptr;
			}

			template<typename T>
			T& get()
			{
				return *reinterpret_cast<T*>(_buff);
			}

		private:
			database			&_db;
			uuid				_id;
			entity				*_entity;
			char				_buff[1];
		};
	}
}

#endif //LIME_ECS_COMPONENET_HPP