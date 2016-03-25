/**
 *
 * @file     input
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/24
 */
#ifndef LIME_ENGINE_INPUT_HPP
#define LIME_ENGINE_INPUT_HPP
#include <lemon/nocopy.hpp>

namespace lime{
	class director;
	class input : private lemon::nocopy
	{
	public:
		input(director *dr) :_director(dr)
		{

		}
		
		virtual ~input(){}

		/**
		* get director view belongs to
		*/
		director * getdirector()
		{
			return _director;
		}


		virtual void run_once() {  }


	private:

		director			*_director;
	};
}

#endif  //LIME_ENGINE_INPUT_HPP