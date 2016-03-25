/**
 *
 * @file     app
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/24
 */
#ifndef LIME_ENGINE_APP_HPP
#define LIME_ENGINE_APP_HPP
#include <string>
#include <chrono>
#include <unordered_map>
#include <lime/engine/lime_errors.hpp>
#include <lime/engine/director.hpp>


namespace lime{

	class application : private lemon::nocopy
	{
	public:
	
		application(const std::string & name):_name(name),_fps(60)
		{

		}

		const std::string & name() { return _name; }

		template<typename Device>
		director* make_director(const std::string & name)
		{
			if(_directors.count(name) != 0)
			{
				throw std::system_error(make_error_code(errc::duplicate_director_name), name);
			}

			auto dr = new director_maker<Device>(this,name);

			_directors[name] = dr;

			return dr;
		}

		void join()
		{
			for(auto dr :_directors)
			{
				dr.second->join();
			}
		}

		unsigned int fps() const
		{
			return _fps;
		}

		void fps(unsigned int val)
		{
			_fps = val;
		}

	private:
		const std::string							_name;
		unsigned int								_fps;		// max fps
		std::unordered_map<std::string, director*>  _directors;
	};
}

#endif  //LIME_ENGINE_APP_HPP