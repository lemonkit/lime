/**
 *
 * @file     events
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/31
 */
#ifndef LIME_ENGINE_EVENTS_HPP
#define LIME_ENGINE_EVENTS_HPP
#include <lemon/nocopy.hpp>

namespace lime{

	class event_dispacther : private lemon::nocopy
	{
	public:
		virtual void dispatch_once() = 0;
	};
}

#endif  //LIME_ENGINE_EVENTS_HPP