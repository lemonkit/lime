#include <lime/device/app.hpp>
#include <lime/engine/director.hpp>

namespace lime{

	void application::run()
	{
		while(true)
		{
			std::size_t closed = 0;

			for (auto kv : _directors)
			{
				if (!kv.second->run_once()) closed++;
			}

			if (closed == _directors.size())
			{
				return; //exit run loop
			}
		}
		
	}
}