#include <lime/sysm/win32/window.hpp>

#ifdef WIN32

#include <mutex>


namespace lime {namespace sysm {

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
	
	window::window(const std::string & name):_hwd(NULL),_name(name)
	{
		static std::once_flag flag;

		std::call_once(flag, [&] { register_lime_class(); });
	}

	window::~window()
	{
		if(_hwd)
		{
			::CloseWindow(_hwd);
		}
	}

	void window::show(int width, int height)
	{
		if (!_hwd)
		{
			int smwidth = GetSystemMetrics(SM_CXSCREEN);

			_hwd = CreateWindowExA(
				0,
				"Lime",
				_name.c_str(),
				WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CLIPCHILDREN,
				smwidth - width, 0, width, height,
				(HWND)NULL, (HMENU)NULL, ::GetModuleHandleA(NULL), (LPVOID)NULL);

			if (!_hwd)
			{
				throw std::system_error(GetLastError(), std::system_category());
			}

			::ShowWindow(_hwd, SW_SHOW);
			::UpdateWindow(_hwd);
		} 
		else 
		{
			::RECT rect;
			::GetWindowRect(_hwd, &rect);
			::MoveWindow(_hwd, rect.left, rect.top, width, height,true);
		}
	}
}}

#endif //WIN32