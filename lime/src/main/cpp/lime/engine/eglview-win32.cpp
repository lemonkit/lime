#include <lime/engine/eglview-win32.hpp>

#if defined(LIME_EGL_VIEW) && defined(WIN32)

#include <mutex>
#include <system_error>

namespace lime{


	LRESULT _winproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	void register_lime_class()
	{
		WNDCLASSA wc = { 0 };

		wc.style = 0;
		wc.lpfnWndProc = (WNDPROC)&_winproc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = NULL;
		wc.lpszClassName = "Lime";
		wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

		if (!RegisterClassA(&wc))
		{
			throw std::system_error(GetLastError(), std::system_category());
		}
	}

	EGLNativeWindowType  eglview_win32:: createWindow(const std::string & name, int width, int height)
	{
		static std::once_flag flag;

		std::call_once(flag, [&] { register_lime_class(); });

		int smwidth = GetSystemMetrics(SM_CXSCREEN);

		auto window = CreateWindowExA(
			0,
			"Lime",
			name.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CLIPCHILDREN,
			smwidth - width, 0, width, height,
			(HWND)NULL, (HMENU)NULL, ::GetModuleHandleA(NULL), (LPVOID)NULL);

		if (!window)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}
		
		::ShowWindow(window, SW_SHOW);
		::UpdateWindow(window);

		return window;
	}
}

#endif //defined(LIME_EGL_VIEW) && defined(WIN32)