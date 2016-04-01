#include <utility>
#include <lime/engine/app.hpp>
#include <lime/engine/director.hpp>

namespace lime{
	app::app()
		:_fps(90), _closed(false)
	{

	}
	app::~app()
	{
		for(auto kv : _directors)
		{
			delete kv.second;
		}
	}

	director* app::create_director(const std::string &name, std::vector<event_dispacther*> && event_dispatchers)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		if(_directors.count(name))
		{
			return _directors[name];
		}

		auto dir = new director(this,name,std::forward<std::vector<event_dispacther*>>(event_dispatchers));

		_directors[name] = dir;

		return dir;
	}

	void app::join()
	{
		std::unique_lock<std::mutex> lock(_mutex);

		while(!_closed)
		{
			_cond.wait(lock);
		}
	}
}