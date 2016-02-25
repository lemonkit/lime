/**
 *
 * @file     main
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifdef WIN32
#include <lime/lime.hpp>
#include <lemon/config.h>

int PASCAL WinMain(HINSTANCE ,HINSTANCE ,LPSTR, int )
{
	lime::application app("lime-simulator");

	 app.register_director("MainDirector", new lime::director(app,"lime",true));

	 app.run();
}

#endif //WIN32