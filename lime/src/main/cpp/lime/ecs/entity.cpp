#include <lime/ecs/entity.hpp>
#include <lime/ecs/database.hpp>
#include <lime/ecs/component.hpp>
namespace lime{
	namespace ecs{

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

			c->attach(this);

			_db.set(c,ec);

			return c;
		}

		component* entity::remove(const uuid & id, std::error_code & ec)
		{
			auto com =  _db.remove(_id,id,ec);

			com->detach();

			return com;
		}

		component* entity::get(const uuid & id, std::error_code & ec) const
		{
			return _db.get(_id, id,ec);
		}
	}
}