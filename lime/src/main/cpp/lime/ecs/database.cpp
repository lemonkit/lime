#include <memory>
#include <lime/ecs/database.hpp>
#include <lime/ecs/ecs_errors.hpp>
#include <lime/ecs/component.hpp>
namespace lime{
	namespace ecs{

		column::column(database &db,const uuid & id,std::size_t nsize,column::F f)
			:_db(db),_id(id),_size(nsize + sizeof(component)), _f(f)
		{

		}

		column:: ~column()
		{
			for(auto kv : _rows)
			{
				auto c = kv.second;
				
				c->~component();

				delete[](char*)c;
			}

			for (auto c : _cached)
			{
				c->~component();

				delete[](char*)c;
			}
		}

		component* column::create()
		{
			if(_cached.empty())
			{
				auto buff = new char[_size];

				auto c = new(buff)component(_db,_id);

				try
				{
					_f(c->buff());
				}
				catch(...)
				{
					delete[] buff;
					throw;
				}
				
				_cached.insert(c);

				return c;
			}

			return *_cached.begin();
		}

		void column::set(component* com, std::error_code & ec)
		{
			if(_cached.count(com) == 0)
			{
				ec = make_error_code(errc::invalid_component);

				return;
			}

			_cached.erase(com);

			auto iter = _rows.find(com->entity_id());

			if (iter != _rows.end())
			{
				iter->second->detach();

				_cached.insert(iter->second);
			}

			_rows[com->entity_id()] = com;
		}
		
		component* column::get(const uuid & id)
		{
			auto iter = _rows.find(id);

			if (iter != _rows.end())
			{
				return iter->second;
			}

			return nullptr;
		}

		component* column::remove(const uuid & id)
		{
			auto iter = _rows.find(id);

			auto com = iter->second;

			_rows.erase(iter);

			return com;
		}

		void column::collect()
		{

		}
		
		database::database()
		{

		}
		
		database::~database()
		{
			for(auto kv :_columns)
			{
				delete kv.second;
			}

			for (auto kv : _rows)
			{
				delete kv.second;
			}

			for (auto kv : _cached)
			{
				delete kv;
			}
		}

		void database::set(component* com, std::error_code & ec)
		{
			if(&com->db() != this)
			{
				ec = make_error_code(errc::invalid_component);
				return;
			}

			if (_rows.count(com->entity_id()) == 0)
			{
				ec = make_error_code(errc::invalid_component);
				return;
			}

			auto iter = _columns.find(com->id());

			if(iter == _columns.end())
			{
				ec = make_error_code(errc::unknown_component_type);
				return;
			}

			iter->second->set(com,ec);
		}

		component* database::get(const uuid & entityid, const uuid & comid, std::error_code & ec) const
		{
			auto iter = _columns.find(comid);

			if (iter == _columns.end())
			{
				ec = make_error_code(errc::unknown_component_type);
				return nullptr;
			}

			return iter->second->get(entityid);
		}

		component* database::remove(const uuid & entityid, const uuid & comid, std::error_code & ec)
		{
			auto iter = _columns.find(comid);

			if (iter == _columns.end())
			{
				ec = make_error_code(errc::unknown_component_type);
				return nullptr;
			}

			return iter->second->remove(entityid);
		}

		component* database::create_component(const uuid & comid)
		{
			auto iter = _columns.find(comid);

			if (iter == _columns.end())
			{
				throw std::system_error(make_error_code(errc::unknown_component_type));
				
			}

			return iter->second->create();
		}


		entity& database::create(const uuid & entityid)
		{
			auto iter = _rows.find(entityid);

			if (iter != _rows.end())
			{
				throw std::system_error(make_error_code(errc::already_exists));
			}

			if(!_cached.empty())
			{
				auto obj = *_cached.begin();

				_cached.erase(_cached.begin());

				obj->id(entityid);

				_rows[entityid] = obj;

				return *obj;
			}

			auto obj = new entity(*this,entityid);

			_rows[entityid] = obj;

			return *obj;
		}

		void database::close(entity* obj)
		{
			for(auto kv : _columns)
			{
				kv.second->remove(obj->id());
			}

			if(1 != _rows.erase(obj->id()))
			{
				throw std::system_error(make_error_code(errc::invalid_entity));
				return;
			}

			_cached.insert(obj);
		}

		void database::collect()
		{
			for(auto kv : _columns)
			{
				kv.second->collect();
			}

			//TODO: performance gc 
		}

		bool database::has(const uuid & entityid) const
		{
			return _rows.count(entityid) != 0;
		}

		entity& database::get(const uuid & entityid) const
		{
			auto iter = _rows.find(entityid);

			if(iter != _rows.end())
			{
				throw std::system_error(errc::invalid_entity);
			}

			return *iter->second;
		}

		void database::create_column(column * cln)
		{
			if(_columns.count(cln->id()) != 0)
			{
				throw std::system_error(make_error_code(errc::duplicate_column_name));
			}

			_columns[cln->id()] = cln;
		}
	}
}