#include <vector>
#include <lime/engine/director.hpp>
#include <lime/engine/lime_errors.hpp>

namespace lime{

	ecs::entity* director::create_scene(const std::string & name)
	{
		if(_scenes.count(name))
		{
			throw std::system_error(make_error_code(errc::duplicate_scene_name));
		}

		auto scene = _db.create();

		scene->garbage_collect_mark();

		_scenes[name] = scene;

		return scene;
	}

	void director::close_scene(const std::string & name)
	{
		auto iter = _scenes.find(name);

		if(iter != _scenes.end())
		{
			iter->second->close();

			_scenes.erase(iter);
		}
	}

	void director::show_scene(const std::string & name)
	{
		auto iter = _scenes.find(name);

		if(iter == _scenes.end())
		{
			throw std::system_error(make_error_code(errc::unknown_scene));
		}

		ecs::entity* prev = iter->second;

		std::swap(prev, _show);

		std::vector<ecs::entity*> stack;

		stack.push_back(prev);

		while(!stack.empty())
		{
			auto current = stack.back();

			stack.pop_back();

			current->visiable(false);

			auto& children = current->children();

			stack.insert(stack.end(),children.begin(),children.end());
		}

		stack.push_back(_show);

		while (!stack.empty())
		{
			auto current = stack.back();

			stack.pop_back();

			current->visiable(false);

			auto& children = current->children();

			stack.insert(stack.end(), children.begin(), children.end());
		}
	}
}