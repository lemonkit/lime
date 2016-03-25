/**
 *
 * @file     win32input
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/25
 */
#ifndef LIME_ENGINE_WIN32INPUT_HPP
#define LIME_ENGINE_WIN32INPUT_HPP
#include <lime/engine/input.hpp>
#ifdef WIN32

namespace lime{
	class win32input : public input
	{
	public:
		using input::input;
		void run_once() override;
	};
}

#endif

#endif  //LIME_ENGINE_WIN32INPUT_HPP