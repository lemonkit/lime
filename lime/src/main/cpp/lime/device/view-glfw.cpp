#include <lime/device/view-glfw.hpp>
#include <lime/errors.hpp>

namespace lime {
	namespace device{
		view_glfw::view_glfw(director *dr, const std::string & name, int width, int height)
			:_director(dr)
		{

			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

			_glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

			if(_glfwWindow == NULL)
			{
				glfwTerminate();
				throw std::system_error(make_error_code(errc::glfw_error),"");
			}

			glfwMakeContextCurrent(_glfwWindow);
		}

		view_glfw::~view_glfw()
		{

		}

		bool view_glfw::run_once()
		{
			if(glfwWindowShouldClose(_glfwWindow)) return false;

			glfwPollEvents();


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(_glfwWindow);

			return true;
		}
	}
}


