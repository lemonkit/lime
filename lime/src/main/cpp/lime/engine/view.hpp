/**
 *
 * @file     view
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/24
 */
#ifndef LIME_ENGINE_VIEW_HPP
#define LIME_ENGINE_VIEW_HPP
#include <lemon/nocopy.hpp>
namespace lime{
	class director;
	class view : private lemon::nocopy
	{
	public:
		view(director *dr):_director(dr)
		{

		}

		virtual ~view() {}

		/**
		 * get director view belongs to
		 */
		director * getdirector()
		{
			return _director;
		}

		virtual void create(int width,int height) = 0;

		virtual void run_once() { }

	private:

		director			*_director;
	};
}
#endif  //LIME_ENGINE_VIEW_HPP