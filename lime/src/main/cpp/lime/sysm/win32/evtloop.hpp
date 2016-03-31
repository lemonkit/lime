/**
 *
 * @file     evtloop
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/31
 */
#ifndef LIME_SYSM_WIN32_EVTLOOP_HPP
#define LIME_SYSM_WIN32_EVTLOOP_HPP
#include <lemon/config.h>
#include <lime/engine/events.hpp>

#ifdef WIN32

namespace lime {namespace sysm {

	class evtloop  : public event_dispacther
	{
	public:
		void dispatch_once() override;
	};

}}

#endif //WIN32

#endif  //LIME_SYSM_WIN32_EVTLOOP_HPP