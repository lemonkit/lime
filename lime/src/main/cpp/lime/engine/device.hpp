/**
 *
 * @file     device
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/24
 */
#ifndef LIME_ENGINE_DEVICE_HPP
#define LIME_ENGINE_DEVICE_HPP

#include <lime/engine/view.hpp>
#include <lime/engine/input.hpp>

namespace lime{
	template <
		typename View = view,
		typename Input = input
	> 
	struct device_maker
	{
		typedef View	view_type;
		typedef Input	input_type;
	};
}

#endif  //LIME_ENGINE_DEVICE_HPP