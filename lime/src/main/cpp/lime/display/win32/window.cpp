#include <lime/display/win32/window.hpp>

#include <mutex>

#ifdef WIN32
namespace lime {namespace win32 {


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
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassA(&wc))
		{
			throw std::system_error(GetLastError(), std::system_category());
		}
	}


	native_window::native_window(const std::string &name , int width, int height)
		:window_system(name,false)
	{
		static std::once_flag flag;

		std::call_once(flag, [&] { register_lime_class(); });

		int x = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
		int y = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

		if (x < 0) x = 0;
		if (y < 0) y = 0;

		auto hwd = CreateWindowExA(
			0,
			"Lime",
			name.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CLIPCHILDREN,
			x,y, width, height,
			(HWND)NULL, (HMENU)NULL, ::GetModuleHandleA(NULL), (LPVOID)NULL);

		if (!hwd)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		::ShowWindow(hwd, SW_SHOW);
		::UpdateWindow(hwd);

		reset(hwd);
	}

	native_window::~native_window()
	{
		::CloseWindow(ptr());
	}

	void native_window::onresize(int width, int height)
	{
		::RECT rect;
		::GetWindowRect(ptr(), &rect);
		::MoveWindow(ptr(), rect.left, rect.top, width, height, true);
	}
}}


#endif //WIN32