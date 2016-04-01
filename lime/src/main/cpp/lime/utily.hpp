/**
 *
 * @file     utily
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/01
 */
#ifndef LIME_RENDER_GLES_UTILY_HPP
#define LIME_RENDER_GLES_UTILY_HPP
#include <string>
#include <sstream>
#include <EGL/egl.h>
#include <lemon/fs/fs.hpp>
#include <lime/errors.hpp>
#include <lemon/log/log.hpp>

namespace lime{

	inline void __throw_error(std::error_code ec,const char * file,int lines, const char *fmt, ...)
	{
		va_list args;

		va_start(args, fmt);

#ifdef WIN32

		int len = vsnprintf(NULL, 0, fmt, args) + 1;

		char *buff = new char[len];

		vsnprintf_s(buff, len, len, fmt, args);
#else
		char *buff;
		int len = vasprintf(&buff, fmt, args);
#endif //WIN32
		va_end(args);

		auto message = std::string(buff, buff + len);

#ifdef WIN32
		delete buff;
#else
		free(buff);
#endif //WIN32

		std::stringstream stream;

		stream << message << " (" << lemon::fs::filepath(file).filename() << ":" << lines;

		throw std::system_error(ec,stream.str());
	}
}

#define limeThrow(ec,fmt,...) lime::__throw_error(ec,__FILE__,__LINE__,(fmt),##__VA_ARGS__)

#endif  //LIME_RENDER_GLES_UTILY_HPP