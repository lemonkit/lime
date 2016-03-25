/**
 *
 * @file     eglview
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/25
 */
#ifndef LIME_ENGINE_EGLVIEW_HPP
#define LIME_ENGINE_EGLVIEW_HPP
#include <string>
#include <lemon/config.h>
#include <lime/engine/config.h>
#include <lime/engine/view.hpp>
#ifdef LIME_EGL_VIEW
#include <EGL/egl.h>
namespace lime{

	class eglview : public view
	{
	public:

		eglview(director *dr);

		~eglview();

		void create(int width, int height);

	private:
		virtual EGLNativeWindowType createWindow(const std::string & name, int width, int height) = 0;
	private:
		EGLDisplay				_display;
		EGLNativeWindowType		_window;
	};
}


#endif //LIME_EGL_VIEW

#endif  //LIME_ENGINE_EGLVIEW_HPP