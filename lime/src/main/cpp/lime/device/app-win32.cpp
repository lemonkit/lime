#include <lime/device/app-win32.hpp>
#include <lemon/log/log.hpp>
#ifdef WIN32
namespace lime {
	namespace device {

		application_win32::application_win32(const std::string &name)
			:_name(name)
		{
			lemon::fs::filepath path = ("./log/");

			path = lemon::fs::absolute(path);

			if(!lemon::fs::exists(path))
			{
				lemon::fs::create_directories(path);
			}

			lemon::log::add_sink(std::unique_ptr<lemon::log::sink>(new lemon::log::file_sink({ name }, path, name)));
		}

		application_win32::~application_win32()
		{
			lemon::log::close();
		}

		void application_win32::run()
		{
			MSG msg;

			while(GetMessage(&msg, NULL, 0, 0) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

#endif //WIN32