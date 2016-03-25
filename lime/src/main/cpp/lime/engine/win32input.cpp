#include <lime/engine/win32input.hpp>

#ifdef WIN32

#include <lemon/config.h>

namespace lime{

	void win32input::run_once()
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

#endif //WIN32