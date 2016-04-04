/**
 * 
 * @file     window
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @date     2016/04/04
 */
#ifndef LIME_DISPLAY_WINDOW_HPP
#define LIME_DISPLAY_WINDOW_HPP
#include <string>
#include <lime/throw.hpp>
#include <lime/errors.hpp>
#include <lime/odb/system.hpp>

namespace lime {
	/*
	 *	the window system
	 */
	class window_system : public system
	{
	public:
		
		/*
		 *	indicate if the window is resizable
		 */
		bool resizable()  const noexcept { return _resizable; }

		void resize(int width,int height) 
		{
			if(!resizable())
			{
				limeThrow(errc::resize_error, "can't resize the window: %s",_name.c_str());
			}

			onresize(width, height);
		}

	private:

		virtual void onresize(int width, int height) = 0;

	protected:
		window_system(const std::string &name,bool fullwindow)
			:_name(name),_resizable(!fullwindow)
		{}

		void resizable(bool flag) noexcept
		{
			_resizable = flag;
		}
	private:
		std::string				_name;
		bool					_resizable;
	};
}

#endif  //LIME_DISPLAY_WINDOW_HPP