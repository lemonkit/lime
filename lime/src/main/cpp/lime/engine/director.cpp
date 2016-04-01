
#include <chrono>
#include <functional>
#include <lime/engine/app.hpp>
#include <lime/engine/director.hpp>
#include <lemon/log/log.hpp>

namespace lime{

	director::director(app * a, const std::string &name,std::vector<event_dispacther*> && dispatchers)
		:_name(name),_running(false), _evtdispatchers(dispatchers),_app(a)
	{

	}


	director::~director()
	{
		if(_worker.joinable())
		{
			_worker.join();
		}

		for(auto dispatcher :_evtdispatchers)
		{
			delete dispatcher;
		}
	}

	void director::start(render *rd, int width, int height)
	{
		_running = true;

		_render.reset(rd);

		_worker = std::thread(std::bind(&director::pcall, this,width,height));
	}

	void director::stop()
	{
		_running = false;
	}

	void director::pcall(int width, int height)
	{
		try
		{
			proc(width, height);
		}
		catch(const std::exception &e)
		{
			lemonE(lemon::log::get("lime"),e.what());
		}
	}

	void director::proc(int width, int height)
	{
		_window.reset(new sysm::window(_name));

		_window->show(width, height);

		_render->attach(_window->ptr());

		typedef std::chrono::high_resolution_clock clock;
		auto start = clock::now();
		auto interval = std::chrono::milliseconds(1000) / _app->fps();
		
		while (_running)
		{
			auto now = clock::now();

			if (now - start >= interval)
			{
				for (auto dispatcher : _evtdispatchers)
				{
					dispatcher->dispatch_once();
				}

				_render->run_once();

				start = now;
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}
}