/**
 *
 * @file     main
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS


#include <lime/lime.hpp>
#include <lemon/config.h>
#include <lemon/log/log.hpp>


int PASCAL WinMain(HINSTANCE ,HINSTANCE ,LPSTR, int )
{
	AllocConsole();
	auto hwndConsole = GetConsoleWindow();
	if (hwndConsole != NULL)
	{
		ShowWindow(hwndConsole, SW_SHOW);
		BringWindowToTop(hwndConsole);
		freopen("CONOUT$", "wt", stdout);
		freopen("CONOUT$", "wt", stderr);
	}

	lemon::log::add_sink(std::unique_ptr<lemon::log::sink>(new lemon::log::console({ "lime" })));

	lime::application app("lime-simulator");

	app.make_director<lime::device_maker<lime::eglview_win32,lime::win32input>>("MainDirector");

	app.join();
}

#endif //WIN32