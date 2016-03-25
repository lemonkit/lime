/**
 *
 * @file     basic_director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/03/24
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP

#include <string>
#include <mutex>
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <condition_variable>


#include <lemon/nocopy.hpp>
#include <lime/engine/view.hpp>

namespace lime{
	class application;
	class director
	{
	public:
		virtual const std::string & name() const = 0;
		virtual void join() = 0;
	};

	/**
	 * the basic game director template class
	 */
	template<typename Device> class director_maker final: public director, private lemon::nocopy
	{
	public:
		typedef Device									device_type;	// device type
		typedef director_maker<device_type>				self_type;		// self class type
		typedef typename device_type::view_type			view_type;		// the view implement
		typedef typename device_type::input_type		input_type;		// input type
	public:
		
		director_maker(application *app,const std::string & name):_app(app),_name(name),_flag(false)
		{
			_view.reset(new view_type(this));
			_input.reset(new input_type(this));
			_worker = std::thread(&self_type::workLoop, this);
		}

		~director_maker()
		{
			close();
			
			_worker.join();
		}

		void close()
		{
			_flag = true;
		}

		void join()
		{
			_worker.join();
		}

		const std::string & name() const 
		{
			return _name;
		}

	private:
		void workLoop()
		{
			typedef std::chrono::high_resolution_clock clock;

			auto start		= clock::now();
			auto interval	= std::chrono::milliseconds(1000) / _app->fps();

			_view->create(1024, 768);

			while(!_flag)
			{
				
				auto now = clock::now();

				if (now - start >= interval)
				{
					_view->run_once();
					_input->run_once();
					start = now;
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}
	private:
		application							*_app;
		std::unique_ptr<view_type>			_view;
		std::unique_ptr<input_type>			_input;
		std::atomic<bool>					_flag;
		std::mutex							_locker;
		std::condition_variable				_cond;
		std::thread							_worker;
		const std::string					_name;
	};
}

#endif  //LIME_ENGINE_DIRECTOR_HPP