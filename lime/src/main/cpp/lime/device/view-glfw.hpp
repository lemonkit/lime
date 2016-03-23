/**
* the lime view implement by GLFW3
* @file     view-glfw
* @brief    Copyright (C) 2016  yayanyang All Rights Reserved
* @author   yayanyang
* @date     2016/02/25
*/
#ifndef LIME_ENGINE_DEVICE_GLFW_HPP
#define LIME_ENGINE_DEVICE_GLFW_HPP

#include <string>
#include <lemon/config.h>
#include <lemon/nocopy.hpp>

namespace lime {
	class director;
	namespace device {

		class view_glfw : private lemon::nocopy
		{
		public:
			view_glfw(director *dr, const std::string & name, int width = 640, int height = 960);
			virtual ~view_glfw();

			void show(bool flag);

			void resolution(int width, int height);
		private:
			director		*_director;
		};

		typedef view_glfw view;
	}
}

#endif // LIME_ENGINE_DEVICE_GLFW_HPP
