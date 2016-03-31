/**
 *
 * @file     window
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/31
 */
#ifndef LIME_SYSM_WIN32_WINDOW_HPP
#define LIME_SYSM_WIN32_WINDOW_HPP
#include <string>
#include <lemon/config.h>
#include <lemon/nocopy.hpp>

#ifdef WIN32

namespace lime{namespace sysm{
	/**
	 * the win32 window system
	 */
	class window : private lemon::nocopy
	{
	public:
		window(const std::string & name);
		
		~window();

		void show(int width,int height);

		/*
		 * get native window handle
		 */
		HWND ptr() const
		{
			return _hwd;
		}

	private:
		HWND					_hwd;	// the win32 windows handler
		std::string				_name;  // window name
	};
}}

#endif //WIN32

#endif  //LIME_SYSM_WIN32_WINDOW_HPP