/**
 *
 * @file     entity
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/22
 */
#ifndef LIME_ECS_ENTITY_HPP
#define LIME_ECS_ENTITY_HPP
#include <list>
#include <vector>
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
		public:
			enum class color 
			{
				white,gray,black
			};
		protected:
			
			friend class database;
			
			entity(database & db,const uuid & id) 
				:_db(db)
				,_id(id)
				,_parent(nullptr)
				,_mark(color::white)
				,_taghash(0)
				,_visiable(false)
			{

			}

			~entity() = default;

		public:

			void visiable(bool flag);
			

			bool visiable() const
			{
				return _visiable;
			}

			/**
			 * get entity's tag name
			 */
			const std::string tag() const
			{
				return _tag;
			}

			/**
			* set entity tag name
			*/
			void tag(const std::string & val)
			{
				_tag = val;
			}

			/**
			* set entity tag name
			*/
			void tag(const std::string && val)
			{
				std::hash<std::string> hasher;
				_tag = val;
				_taghash = hasher(_tag);
			}

			/*
			 * close this entity and children
			 */
			void close()
			{
				for(auto child : _children)
				{
					child->close();
				}

				_db.close(this);

				_mark = color::black;
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

			void remove(const uuid & id, std::error_code & ec);

			void remove(const uuid & id)
			{
				std::error_code ec;
				remove(id, ec);
				if (ec)
				{
					throw std::system_error(ec);
				}
			}
			
			component* get(const uuid & id) const;

			/**
			 * get component's value
			 */
			template<typename T>
			T* get(const uuid & id)
			{
				auto c = get(id);

				if (c) return c->get<T>();

				return nullptr;
			}

			/**
			 * add child node 
			 */
			void add_child(entity * child)
			{
				child->remove_from_parent();

				for (auto c :_children)
				{
					if(c == child)
					{
						return;
					}
				}

				_children.push_back(child);

				child->_parent = this;
			}

			/**
			 * remove child node
			 */
			bool remove_child(entity *child)
			{
				for (auto iter = _children.begin(); iter != _children.end(); iter++)
				{
					if (*iter == child)
					{
						(*iter)->garbage_collect_unmark();

						_children.erase(iter);

						return true;
					}
				}

				return false;
			}

			/**
			 * remove child node by node tag
			 */
			bool remove_child(const std::string & tagname)
			{
				std::hash<std::string> hasher;

				auto hashcode = hasher(tagname);

				for (auto iter = _children.begin(); iter != _children.end(); iter++)
				{
					if ((*iter)->_taghash == hashcode && (*iter)->tag() == tagname)
					{
						(*iter)->garbage_collect_unmark();

						_children.erase(iter);

						return true;
					}
				}

				return false;
			}

			/**
			 * remove entity from parent node
			 */
			void remove_from_parent()
			{
				if(_parent)
				{
					_parent->remove_child(this);
				}
			}

			void garbage_collect_unmark()
			{
				if (_mark == color::white) return;

				_mark = color::white;

				_db.garbage_collect_unmark(this);

				for (auto child : _children)
				{
					child->garbage_collect_unmark();
				}
			}

			/**
			 * process mark-sweep GC algorithm mark period
			 */
			void garbage_collect_mark()
			{
				if (_mark == color::gray) return;

				_mark = color::gray;

				_db.garbage_collect_mark(this);

				for(auto child : _children)
				{
					child->garbage_collect_mark();
				}
			}

			const std::vector<entity*>& children() const
			{
				return _children;
			}

		private:
			database							&_db;
			uuid								_id;
			std::string							_tag;
			std::size_t							_taghash;
			entity*								_parent;
			std::vector<entity*>				_children;
			std::vector<component*>				_components;
			color								_mark;
			bool								_visiable;
		};
	}
}

#endif //LIME_ECS_ENTITY_HPP