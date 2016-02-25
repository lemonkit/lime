/**
 *
 * @file     app-win32
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifndef LIME_ENGINE_DEVICE_APP_HPP
#define LIME_ENGINE_DEVICE_APP_HPP
#ifdef WIN32
#include <locale>
#include <string>
#include <unordered_map>
#include <lemon/nocopy.hpp>
#include <lime/device/view-win32.hpp>

namespace lime{

	class director;

	namespace device {

		using string_convert = std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t>;

		class application_win32 : private lemon::nocopy
		{
		public:
			application_win32(const std::string &name);

			virtual ~application_win32();

			const std::string & name() const
			{
				return _name;
			}

			void run();

		private:
			const std::string _name;
		};

		typedef application_win32 application;
	}
}

#endif //WIN32
#endif //LIME_ENGINE_DEVICE_APP_HPP