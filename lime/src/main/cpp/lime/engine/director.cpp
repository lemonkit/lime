#include <lime/engine/director.hpp>


namespace lime{

	director::director(application & app, const std::string & name,bool general)
		:_app(app), _logger(lemon::log::get(app.name())),_general(general)
	{
		_view = new device::view(this,name);

		_view->show(true);
	}

	director::~director()
	{
		delete _view;

		for(auto sym :_systems)
		{
			delete sym;
		}
	}

	void director::register_system(system* sysm, std::error_code &ec)
	{
		if(this->sysm(sysm->id()))
		{
			ec = make_error_code(errc::duplicate_system_name);
			return;
		}

		_systems.push_back(sysm);
	}

	system* director::sysm(const sid & id)
	{
		std::hash<sid> hasher;
		std::size_t hashcode = hasher(id);

		for(auto sysm :_systems)
		{
			if(sysm->hashcode() == hashcode && sysm->id() == id)
			{
				return sysm;
			}
		}

		return nullptr;
	}

	void director::run_once() noexcept
	{
		
	}
}