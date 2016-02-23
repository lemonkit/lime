#include <memory>
#include <lime/ecs/database.hpp>
#include <lime/ecs/ecs_errors.hpp>
#include <lime/ecs/component.hpp>
namespace lime{
	namespace ecs{

		column::column(database &db,const uuid & id,std::size_t nsize,column::F createf, column::F closef)
			:_db(db),_id(id),_size(nsize + sizeof(component)), _createf(createf),_closef(closef)
		{

		}

		column:: ~column()
		{
			for(auto kv : _rows)
			{
				auto c = kv.second;

				_closef(c->buff());
				
				c->~component();

				delete[](char*)c;
			}

		}

		component* column::create()
		{
			auto buff = new char[_size];

			auto c = new(buff)component(_db, *this, _id);

			try
			{
				_createf(c->buff());
			}
			catch (...)
			{
				delete[] buff;
				throw;
			}

			return c;
		}

		void column::set(component* com, std::error_code &)
		{
			auto iter = _rows.find(com->entity_id());

			if (iter != _rows.end())
			{
				iter->second->detach();

				_closef(iter->second->buff());

				iter->second->~component();

				delete[] (char*)iter->second;
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

		void column::remove(const uuid & id)
		{
			auto iter = _rows.find(id);

			if(iter != _rows.end())
			{
				iter->second->detach();

				_closef(iter->second->buff());

				iter->second->~component();

				delete[](char*)iter->second;

				_rows.erase(iter);
			}
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

		}

		void database::set(component* com, std::error_code & ec)
		{
			if(&com->db() != this)
			{
				ec = make_error_code(errc::invalid_component);
				return;
			}

			if (_rows.count(com->entity_id()) == 0 && _marked.count(com->entity_id()) == 0)
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

		void database::remove(const uuid & entityid, const uuid & comid, std::error_code & ec)
		{
			auto iter = _columns.find(comid);

			if (iter == _columns.end())
			{
				ec = make_error_code(errc::unknown_component_type);
			}

			iter->second->remove(entityid);
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


		entity* database::create(const uuid & entityid)
		{
			if (_rows.count(entityid) != 0 || _marked.count(entityid) != 0)
			{
				throw std::system_error(make_error_code(errc::already_exists));
			}

			auto obj = new entity(*this,entityid);

			_rows[entityid] = obj;

			return obj;
		}

		void database::close(entity* obj)
		{
			for(auto kv : _columns)
			{
				kv.second->remove(obj->id());
			}

			if(1 != _rows.erase(obj->id()) && 1 != _marked.erase(obj->id()))
			{
				throw std::system_error(make_error_code(errc::invalid_entity));
				return;
			}

			delete obj;
		}

		void database::garbage_collect()
		{
			for(auto kv:_rows)
			{
				for (auto kv2 : _columns)
				{
					kv2.second->remove(kv.second->id());
				}

				delete kv.second;
			}

			_rows.clear();
		}

	
		entity* database::get(const uuid & entityid) const
		{
			auto iter = _rows.find(entityid);

			if(iter == _rows.end())
			{
				iter = _marked.find(entityid);

				if(iter == _marked.end())
				{
					return nullptr;
				}
			}

			return iter->second;
		}

		void database::create_column(column * cln)
		{
			if(_columns.count(cln->id()) != 0)
			{
				throw std::system_error(make_error_code(errc::duplicate_column_name));
			}

			_columns[cln->id()] = cln;
		}

		void database::garbage_collect_mark(entity * obj)
		{
			if(_rows.erase(obj->id()) != 1)
			{
				throw std::system_error(make_error_code(errc::invalid_entity));
			}

			_marked[obj->id()] = obj;
		}

		void database::garbage_collect_unmark(entity * obj)
		{
			if (_marked.erase(obj->id()) != 1)
			{
				throw std::system_error(make_error_code(errc::invalid_entity));
			}

			_rows[obj->id()] = obj;
		}
	}
}