/**
 *
 * @file     eglview-win32
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/25
 */
#ifndef LIME_ENGINE_EGLVIEW_WIN32_HPP
#define LIME_ENGINE_EGLVIEW_WIN32_HPP

#include <lime/engine/eglview.hpp>

#if defined(LIME_EGL_VIEW) && defined(WIN32)

#include <lemon/config.h>

namespace lime {

	class eglview_win32 : public eglview
	{
	public:
		eglview_win32(director *dr):eglview(dr),_window(NULL)
		{

		}

		~eglview_win32()
		{
			CloseWindow(_window);
		}
	private:

		EGLNativeWindowType createWindow(const std::string & name, int width, int height) override;

	private:
		EGLNativeWindowType _window;
	};
}

#endif

#endif  //LIME_ENGINE_EGLVIEW_WIN32_HPP