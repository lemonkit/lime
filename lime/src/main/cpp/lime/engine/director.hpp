/**
 *
 * @file     director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/31
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP

#include <mutex>
#include <vector>
#include <atomic>
#include <string>
#include <memory>
#include <thread>
#include <unordered_set>
#include <lemon/nocopy.hpp>
#include <lime/sysm/sysm.hpp>
#include <lime/engine/app.hpp>
#include <lime/engine/events.hpp>
#include <lime/engine/render.hpp>

namespace lime{
	class app;
	class director final : private lemon::nocopy
	{
		friend class app;
	protected:
		/**
		 * create director with name and event dispatchers
		 */
		director(app * a, const std::string &name,std::vector<event_dispacther*> && event_dispatchers);
		
		~director();
	public:
		/**
		 * start director
		 */
		void start(render *rd, int width,int height);
		/**
		 * stop director
		 */
		void stop();

	private:
		void proc(int width, int height);
		void pcall(int width, int height);
	private:
		std::string								_name;
		std::atomic_bool						_running;
		std::thread								_worker;
		std::unique_ptr<sysm::window>			_window;
		std::unique_ptr<render>					_render;
		std::vector<event_dispacther*>			_evtdispatchers;
		app										*_app;
	};
}



#endif  //LIME_ENGINE_DIRECTOR_HPP