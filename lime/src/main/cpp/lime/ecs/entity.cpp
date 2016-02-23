#include <lime/ecs/entity.hpp>
#include <lime/ecs/database.hpp>
#include <lime/ecs/component.hpp>
namespace lime{
	namespace ecs{

		void entity::visiable(bool flag)
		{
			_visiable = flag;
		}

		component* entity::set(const uuid & id, std::error_code & ec)
		{

			component * c;

			try
			{
				c = _db.create_component(id);
			}
			catch(const std::system_error & e)
			{
				ec = e.code();

				return nullptr;
			}

			if(get(id) != nullptr)
			{
				ec = make_error_code(errc::duplicate_column_name);

				return nullptr;
			}

			c->attach(this);

			_db.set(c,ec);

			_components.push_back(c);

			return c;
		}

		void entity::remove(const uuid & id, std::error_code & ec)
		{
			_db.remove(_id,id,ec);

			for (auto iter = _components.begin(); iter != _components.end(); iter++)
			{
				if ((*iter)->id() == id)
				{
					_components.erase(iter);
				}
			}
		}

		component* entity::get(const uuid & id) const
		{
			for(auto c: _components)
			{
				if(c->id() == id)
				{
					return c;
				}
			}

			return nullptr;
		}
	}
}