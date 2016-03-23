/**
*
* @file     device
* @brief    Copyright (C) 2016  yayanyang All Rights Reserved
* @author   yayanyang
* @date     2016/02/25
*/

#ifndef LIME_DEVICE_APP_HPP
#define LIME_DEVICE_APP_HPP

#include <string>
#include <unordered_map>

#ifdef WIN32
#include <lime/device/app-win32.hpp>
#endif

#ifdef WIN32_NATIVE_VIEW
#include <lime/device/view-win32.hpp>
#else
#include <lime/device/view-glfw.hpp>
#endif 

#include <lime/errors.hpp>

namespace lime {

	class director;

	class application : public device::application
	{
	public:
		application(const std::string & name) :device::application(name)
		{

		}

		void register_director(const std::string &name, director* dr)
		{
			if (_directors.count(name))
			{
				throw std::system_error(make_error_code(errc::duplicate_director_name));
			}

			_directors[name] = dr;
		}

		void unregister_director(const std::string &name)
		{
			_directors.erase(name);
		}

	private:
		bool										_exit;
		std::unordered_map<std::string, director*>	_directors;
	};
}

#endif //LIME_DEVICE_HPP
