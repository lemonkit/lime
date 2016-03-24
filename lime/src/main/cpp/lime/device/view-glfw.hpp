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
#include <GLFW/glfw3.h>

namespace lime {
	class director;
	namespace device {

		class view_glfw : private lemon::nocopy
		{
		public:
			view_glfw(director *dr, const std::string & name, int width = 640, int height = 960);
			virtual ~view_glfw();

			virtual void show(bool ) {};
			virtual void resolution(int , int ) {};

			bool run_once();
		private:
			director		*_director;
			GLFWwindow		*_glfwWindow;
		};

		typedef view_glfw view;
	}
}

#endif // LIME_ENGINE_DEVICE_GLFW_HPP
