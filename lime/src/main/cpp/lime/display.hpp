/**
 *
 * @file     display
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/05
 */
#ifndef LIME_DISPLAY_HPP
#define LIME_DISPLAY_HPP

#include <lime/display/window.hpp>

#ifdef WIN32
#include <lime/display/win32/window.hpp>

namespace lime{
	using window = lime::win32::native_window;
}

#endif //WIN32



#endif  //LIME_DISPLAY_HPP


