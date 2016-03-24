/**
 *
 * @file     view-win32
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifndef LIME_ENGINE_DEVICE_VIEW_HPP
#define LIME_ENGINE_DEVICE_VIEW_HPP

#ifdef WIN32_NATIVE_VIEW
#include <string>
#include <lemon/config.h>
#include <lemon/nocopy.hpp>


namespace lime{
	class director;
	namespace device{

		class view_win32 : private lemon::nocopy
		{
		public:

			view_win32(director *dr, const std::string & name, int width = 640, int height = 960);
			virtual ~view_win32();

			void show(bool flag);

			void resolution(int width,int height);

		private:
			void register_lime_class();

			static LRESULT _winproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

			LRESULT winproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		private:
			HWND			_view; // win32 windows handle
			director		*_director;
		};


		typedef view_win32 view;
	}
}

#endif //WIN32

#endif //LIME_ENGINE_DEVICE_VIEW_HPP