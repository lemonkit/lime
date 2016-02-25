#include <mutex>
#include <lime/device/app-win32.hpp>
#include <lime/device/view-win32.hpp>
#include <lime/engine/director.hpp>

#ifdef WIN32

#define MainWndName "LimeMainDirector"

namespace lime{
	namespace device{

		LRESULT view_win32::_winproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			auto v = (view_win32*)::GetWindowLongPtrA(hWnd, GWLP_USERDATA);
			return v->winproc(hWnd, Msg, wParam, lParam);
		}

		void view_win32::register_lime_class()
		{
			WNDCLASSA wc = { 0 };

			wc.style = 0;
			wc.lpfnWndProc = (WNDPROC)&view_win32::_winproc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = NULL;
			wc.lpszClassName = MainWndName;
			wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

			if(!RegisterClassA(&wc))
			{
				throw std::system_error(GetLastError(),std::system_category());
			}
		}

		view_win32::view_win32(director *dr, const std::string & name,int width, int height)
			:_director(dr)
		{
			static std::once_flag flag;

			std::call_once(flag, [&] { view_win32::register_lime_class(); });

			string_convert conv;

			int smwidth = GetSystemMetrics(SM_CXSCREEN);

			_view = CreateWindowExA(
				0,
				MainWndName,
				name.c_str(),
				WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU |WS_CLIPCHILDREN,
				smwidth - width,0, width, height,
				(HWND)NULL,(HMENU)NULL,::GetModuleHandleA(NULL), (LPVOID)NULL);

			if(!_view)
			{
				throw std::system_error(GetLastError(),std::system_category());
			}

			::SetWindowLongPtrA(_view, GWLP_USERDATA, (LONG)this);
		}

		view_win32::~view_win32()
		{
			DestroyWindow(_view);
		}

		void view_win32::show(bool flag)
		{
			::ShowWindow(_view, flag ? 1 : 0);
			::UpdateWindow(_view);
		}

		void view_win32::resolution(int width, int height)
		{
			RECT rc;

			int smwidth = GetSystemMetrics(SM_CXSCREEN);
			
			::GetWindowRect(_view, &rc);

			::MoveWindow(_view, smwidth - width, 0, width, height,true);
		}

		LRESULT view_win32::winproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			if (Msg == WM_CLOSE &&_director->general_director())
			{
				::PostMessage(hWnd, WM_QUIT, wParam, lParam);
			}

			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}
	}

}
#endif //WIN32