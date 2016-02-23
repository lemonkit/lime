/**
 *
 * @file     system
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/23
 */
#ifndef LIME_ECS_SYSTEM_HPP
#define LIME_ECS_SYSTEM_HPP

#include <lemon/nocopy.hpp>
#include <lime/ecs/component.hpp>

namespace lime{
	namespace ecs{

		class system : private lemon::nocopy
		{
		public:

			system(const uuid &id):_id(id){}

			const uuid & id() const
			{
				return _id;
			}

			virtual ~system() {}

			virtual void process(component * c) = 0;

		private:
			uuid				_id;
		};
	}
}

#endif //LIME_ECS_SYSTEM_HPP