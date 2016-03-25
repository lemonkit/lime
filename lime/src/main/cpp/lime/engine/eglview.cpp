#include <lime/engine/eglview.hpp>

#ifdef LIME_EGL_VIEW
#include <sstream>
#include <lemon/log/log.hpp>
#include <lime/engine/lime_errors.hpp>
#include <lime/engine/director.hpp>

auto &logger = lemon::log::get("lime");

namespace lime{

	eglview::eglview(director *dr):view(dr)
	{
		lemonD(logger, "eglGetDisplay");

		_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		if (_display == EGL_NO_DISPLAY)
		{
			std::stringstream stream;

			stream << "eglGetDisplay error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

		lemonD(logger, "eglInitialize");

		EGLint manjor, minor;

		if(!eglInitialize(_display,&manjor,&minor))
		{
			std::stringstream stream;

			stream << "eglInitialize error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}
	}

	eglview::~eglview()
	{

	}

	void eglview::create(int width, int height)
	{
		_window = createWindow(getdirector()->name(), width, height);
	}
}
#endif //LIME_EGL_VIEW