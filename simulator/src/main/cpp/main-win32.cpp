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

	lime::app app;

	auto mainDirector = app.create_director("main", { new lime::sysm::evtloop() });

	mainDirector->start(new lime::gles::render(),800, 600);

	app.join();
}

#endif //WIN32