#include <lime/sysm/win32/evtloop.hpp>

#ifdef WIN32

namespace lime {namespace sysm {

	void evtloop::dispatch_once() 
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}}

#endif //WIN32