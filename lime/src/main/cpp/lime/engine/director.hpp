/**
 *
 * @file     director
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifndef LIME_ENGINE_DIRECTOR_HPP
#define LIME_ENGINE_DIRECTOR_HPP
#include <type_traits>

#include <lemon/log/log.hpp>

#include <lime/odb/odb.hpp>
#include <lime/engine/system.hpp>
#include <lime/engine/lime_errors.hpp>
#include <lime/device/device.hpp>

namespace lime{
	
	class application;
	class director : lemon::nocopy
	{
	public:

		director(application & app,const std::string & name,bool general = false);

		~director();

		odb::database & db() 
		{
			return _db;
		}

		const odb::database & db() const
		{
			return _db;
		}
		
		template<typename T,typename ... Args>
		void register_system(const sid& id,Args ...args)
		{
			static_assert(std::is_convertible<T*,system*>::value,"T must inherit from lime::system");

			register_system(new T(id, std::forward<Args>(args)...));
		}

	public:
		
		device::view* view()
		{
			return _view;
		}

		bool run_once() noexcept;

		bool general_director() const
		{
			return _general;
		}

	private:
		
		void register_system(system* sysm,std::error_code &ec);

		system* sysm(const sid & id);

	private:
		odb::database						_db;
		std::vector<system*>				_systems;
		application							&_app;
		const lemon::log::logger			&_logger;
		device::view						*_view;
		bool								_general;
	};
}

#endif //LIME_ENGINE_DIRECTOR_HPP