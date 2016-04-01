/**
 *
 * @file     app
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/01
 */
#ifndef LIME_ENGINE_APP_HPP
#define LIME_ENGINE_APP_HPP

#include <mutex>
#include <cstdint>
#include <unordered_map>
#include <lemon/nocopy.hpp>
#include <lime/engine/events.hpp>

namespace lime{

	class director;
	class app : private lemon::nocopy
	{
	public:
		
		app();
		
		~app();

		std::uint8_t fps() const
		{
			return _fps;
		}

		void fps(std::uint8_t val)
		{
			_fps = val;
		}

		director* create_director(const std::string &name, std::vector<event_dispacther*> && event_dispatchers);

		void join();

	private:
		bool												_closed;
		std::uint8_t										_fps;
		std::mutex											_mutex;
		std::condition_variable								_cond;
		std::unordered_map < std::string, director*>		_directors;
	};
}

#endif  //LIME_ENGINE_APP_HPP