/**
 *
 * @file     window
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/05
 */
#ifndef LIME_DISPLAY_WIN32_WINDOW_HPP
#define LIME_DISPLAY_WIN32_WINDOW_HPP
#include <lime/display/window.hpp>

#ifdef WIN32

namespace lime{ namespace win32{
	
	class native_window : public window_system
	{
	public:
		native_window(const std::string &name,int width,int height);
		
		~native_window();
		
		void onresize(int width, int height) override;
	};
}}

#endif //WIN32

#endif  //LIME_DISPLAY_WIN32_WINDOW_HPP