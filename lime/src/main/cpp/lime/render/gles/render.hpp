/**
 *
 * @file     render
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/01
 */
#ifndef LIME_RENDER_GLES_RENDER_HPP
#define LIME_RENDER_GLES_RENDER_HPP

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <EGL/eglext.h>
#include <lime/errors.hpp>
#include <lime/engine/render.hpp>
#include <lime/utily.hpp>

namespace lime{ namespace gles{

	class render : public lime::render
	{
	public:

		render():render(EGL_DEFAULT_DISPLAY)
		{

		}

		render(EGLNativeDisplayType displayID)
		{
			eglopen(displayID);
		}

		void attach(void *window) override
		{
			_config = choose_config();

			_surface = eglCreateWindowSurface(_display, _config, (EGLNativeWindowType)window, NULL);

			if(_surface == EGL_NO_SURFACE)
			{
				limeThrow(errc::egl_error, "eglCreateWindowSurface error :%d", eglGetError());
			}

			_context = create_context();
		}
		
		void run_once() override
		{
			eglSwapBuffers(_display, _surface);
		}

	protected:

		void eglopen(EGLNativeDisplayType displayID)
		{
			_display = eglGetDisplay(displayID);

			if (_display == EGL_NO_DISPLAY)
			{
				limeThrow(errc::egl_error, "eglGetDisplay error :%d", eglGetError());
			}

			EGLint major, minor;

			if (!eglInitialize(_display, &major, &minor))
			{
				limeThrow(errc::egl_error, "eglInitialize error :%d", eglGetError());
			}
		}

		virtual EGLContext create_context()
		{
			const EGLint attribs[] =
			{
				EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR,
				EGL_CONTEXT_CLIENT_VERSION,3,
				EGL_CONTEXT_MAJOR_VERSION_KHR,3,
				EGL_NONE
			};

			EGLContext context = eglCreateContext(_display, _config, EGL_NO_CONTEXT, attribs);

			if (context == EGL_NO_CONTEXT)
			{
				limeThrow(errc::egl_error, "eglCreateContext error :%d", eglGetError());
			}

			if(EGL_FALSE == eglMakeCurrent(_display, _surface, _surface, context))
			{
				limeThrow(errc::egl_error, "eglMakeCurrent error :%d", eglGetError());
			}

			return context;
		}

		virtual EGLConfig choose_config()
		{
			EGLint attribs[] = 
			{
				EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT_KHR,
				EGL_RED_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_BLUE_SIZE, 8,
				EGL_DEPTH_SIZE, 16,
				EGL_NONE
			};

			EGLint numConfigs;

			EGLConfig config;

			if(!eglChooseConfig(_display,attribs,&config,1,&numConfigs))
			{
				limeThrow(errc::egl_error, "eglChooseConfig error :%d", eglGetError());
			}

			return config;
		}

	private:

		EGLDisplay			_display;
		EGLSurface			_surface;
		EGLContext			_context;
		EGLConfig			_config;
	};
}}

#endif  //LIME_RENDER_GLES_RENDER_HPP