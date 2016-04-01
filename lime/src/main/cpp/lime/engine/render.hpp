/**
 *
 * @file     render
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/01
 */
#ifndef LIME_ENGINE_RENDER_HPP
#define LIME_ENGINE_RENDER_HPP

#include <lemon/nocopy.hpp>

namespace lime{

	class render : private lemon::nocopy
	{
	public:
		virtual void attach(void *window) = 0;
		virtual void run_once() = 0;
	};
}

#endif  //LIME_ENGINE_RENDER_HPP