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
		
	}

	eglview::~eglview()
	{

	}

	void eglview::create(int width, int height)
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

		if (!eglInitialize(_display, &manjor, &minor))
		{
			std::stringstream stream;

			stream << "eglInitialize error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

		EGLNativeWindowType window = createWindow(getdirector()->name(), width, height);

		// create window surface

		EGLConfig configs[1];

		EGLint numOfConfigs = 0;

		EGLint configAttrs[] = { 
			EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
			EGL_NONE 
		};

		if(!eglChooseConfig(_display, configAttrs,configs,sizeof(configs)/sizeof(EGLConfig),&numOfConfigs))
		{
			std::stringstream stream;

			stream << "eglChooseConfig error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

		EGLint windowAttrs[] = {
			EGL_RENDER_BUFFER,EGL_BACK_BUFFER,
			EGL_NONE
		};

		_surface = eglCreateWindowSurface(_display, configs[0], window, windowAttrs);

		if (_surface == EGL_NO_SURFACE)
		{
			std::stringstream stream;

			stream << "eglCreateWindowSurface error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

		EGLint contextAttrs[] =
		{
			EGL_CONTEXT_CLIENT_VERSION,2,
			EGL_NONE
		};

		_context = eglCreateContext(_display, configs[0], EGL_NO_CONTEXT, contextAttrs);

		if (_context == EGL_NO_CONTEXT)
		{
			std::stringstream stream;

			stream << "eglCreateContext error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

		if(!eglMakeCurrent(_display,_surface,_surface,_context))
		{
			std::stringstream stream;

			stream << "eglMakeCurrent error :" << eglGetError();

			throw std::system_error(errc::egl_error, stream.str());
		}

	}
}
#endif //LIME_EGL_VIEW