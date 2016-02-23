/**
 *
 * @file     director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/23
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP

#include <string>
#include <unordered_map>
#include <lemon/nocopy.hpp>
#include <lime/ecs/ecs.hpp>

namespace lime {

	class director : lemon::nocopy
	{
	public:

		director():_show(nullptr) {}
		
		ecs::entity* create_scene(const std::string & name);
		
		void close_scene(const std::string & name);

		void show_scene(const std::string & name);

		ecs::entity* scene() const
		{
			return _show;
		}

	private:
		
		ecs::database									_db;

		ecs::entity*									_show;

		std::unordered_map<std::string, ecs::entity*>	_scenes;
	};

}

#endif //LIME_ENGINE_DIRECTOR_HPP