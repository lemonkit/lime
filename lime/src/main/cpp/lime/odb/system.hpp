/**
 * 
 * @file     system
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @date     2016/04/04
 */
#ifndef LIME_ODB_SYSTEM_HPP
#define LIME_ODB_SYSTEM_HPP
#include <lemon/nocopy.hpp>
namespace lime {
	/*
	 *	the ECS system interface
	 */
	class system : private lemon::nocopy
	{
	public:
		/*
		 *	run the system once
		 */
		virtual void run_once() = 0;
	};
}

#endif  //LIME_ODB_SYSTEM_HPP