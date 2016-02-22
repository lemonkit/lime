#include <lime/ecs/entity.hpp>
#include <lime/ecs/component.hpp>


namespace lime{
	namespace ecs{

		void component::attach(entity * obj)
		{
			_entity = obj;
		}

		entity* component::detach()
		{
			return _entity;
		}
	}
}