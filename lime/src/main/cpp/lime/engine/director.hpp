/**
 *
 * @file     director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/23
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP

#include <mutex>
#include <string>
#include <unordered_map>
#include <lemon/nocopy.hpp>
#include <lime/ecs/ecs.hpp>
#include <condition_variable>

namespace lime {

	class director : lemon::nocopy
	{
	public:

		director():_show(nullptr),_exit(false) {}
		
		ecs::entity* create_scene(const std::string & name);
		
		void close_scene(const std::string & name);

		void show_scene(const std::string & name);

		ecs::entity* scene() const
		{
			return _show;
		}

		void register_system(ecs::system *sym);

		void run();
	
	private:
		
		ecs::database												_db;

		ecs::entity*												_show;

		std::unordered_map<std::string, ecs::entity*>				_scenes;

		std::unordered_map<lemon::uuids::uuid, ecs::system*>		_syms;

		bool														_exit;

		std::condition_variable										_cond;

		std::mutex													_mutex;
	};

}

#endif //LIME_ENGINE_DIRECTOR_HPP