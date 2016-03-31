/**
 *
 * @file     director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/31
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP

#include <lemon/nocopy.hpp>

#ifdef WIN32

namespace lime{

	class director : private lemon::nocopy
	{

	};
}

#endif //WIN32

#endif  //LIME_ENGINE_DIRECTOR_HPP