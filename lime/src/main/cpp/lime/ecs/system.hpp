/**
 * 
 * @file     system
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @date     2016/04/04
 */
#ifndef LIME_ODB_SYSTEM_HPP
#define LIME_ODB_SYSTEM_HPP
#include <string>
#include <lemon/nocopy.hpp>

namespace lime {namespace ecs{	

	class table;
	class database;

	/*
	 *	the ECS system interface
	 */
	class system : private lemon::nocopy
	{
	public:
		/*
		 *	run the system once
		 */
		virtual void run_once(table &tl) = 0;
		/*
		 *	register ecs components
		 */
		virtual void register_components(database & db) = 0;
	};
}}

#endif  //LIME_ODB_SYSTEM_HPP