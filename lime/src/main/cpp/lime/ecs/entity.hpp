/**
 *
 * @file     entity
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/22
 */
#ifndef LIME_ECS_ENTITY_HPP
#define LIME_ECS_ENTITY_HPP
#include <system_error>
#include <lemon/uuid.hpp>
#include <lemon/nocopy.hpp>
#include <lime/ecs/database.hpp>
#include <lime/ecs/ecs_errors.hpp>
namespace lime{
	namespace ecs{

		using uuid = lemon::uuids::uuid;

		class component;

		class entity final : private lemon::nocopy
		{
		protected:
			friend class database;
			entity(database & db,const uuid & id) :_db(db),_id(id) {}

			~entity() = default;

		public:

			void close()
			{
				_db.close(this);
			}

			const uuid & id() const
			{
				return _id;
			}

			void id(const uuid & newid)
			{
				this->_id = newid;
			}
			
			component* set(const uuid & id, std::error_code & ec);

			inline component* set(const uuid & id)
			{
				std::error_code ec;
				auto c = set(id,ec);
				if(ec)
				{
					throw std::system_error(ec);
				}

				return c;
			}

			component* remove(const uuid & id, std::error_code & ec);

			component* remove(const uuid & id)
			{
				std::error_code ec;
				auto c = remove(id, ec);
				if (ec)
				{
					throw std::system_error(ec);
				}

				return c;
			}
			
			component* get(const uuid & id, std::error_code & ec) const;

			component* get(const uuid & id) const
			{
				std::error_code ec;
				auto c = get(id, ec);
				if (ec)
				{
					throw std::system_error(ec);
				}

				return c;

			}

			template<typename T>
			T& get(const uuid & id)
			{
				auto c = get(id);

				if (c) return c->get<T>();

				throw std::system_error(make_error_code(errc::unknown_component_type));
			}

			bool has(const uuid & id) 
			{
				std::error_code ec;

				if(get(id,ec))
				{
					return true;
				}

				if(ec == errc::unknown_component_type)
				{
					return false;
				}

				throw std::system_error(ec);
			}

		private:
			database							&_db;
			uuid								_id;
		};
	}
}

#endif //LIME_ECS_ENTITY_HPP