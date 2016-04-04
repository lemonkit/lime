#include <lime/log.hpp>

namespace lime {namespace log{
	const lemon::log::logger &logger	= lemon::log::get("lime");
	const lemon::log::logger &odb		= lemon::log::get("lime-odb");
}}