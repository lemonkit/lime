#ifndef LIME_ERRORS_HPP
#define LIME_ERRORS_HPP

#include <string>
#include <system_error>

namespace lime {
	enum class errc
	{
		duplicate_scene_name = 1, unknown_scene, duplicate_system_name,duplicate_director_name,glfw_error
	};

	class ecs_error_category : public std::error_category
	{
	private:

		const char *name() const throw()
		{
			return "lemon::os::os_error_category";
		}

		std::string message(int val) const
		{
			switch ((errc)val)
			{
			case errc::duplicate_scene_name:
				return "duplicate scene name";
			case errc::unknown_scene:
				return "unknown scene";
			case errc::duplicate_system_name:
				return "duplicate system name";
			case errc::duplicate_director_name:
				return "duplicate director name";
			case errc::glfw_error:
				return "glfw error";
			}

			return "unknown";
		}

		std::error_condition default_error_condition(int _Errval) const throw()
		{
			return std::error_condition(_Errval, *this);
		}

		bool equivalent(int _Errval, const std::error_condition& _Cond) const throw()
		{
			return _Errval == _Cond.value();
		}

		bool equivalent(const std::error_code& _Code, int _Errval) const throw()
		{
			return _Errval == _Code.value();
		}
	};

	inline std::error_code make_error_code(errc err) noexcept
	{
		static ecs_error_category error_category;

		return std::error_code(static_cast<int>(err), error_category);
	}

}

namespace std {
	template<> struct is_error_code_enum<::lime::errc> : true_type {};
}
#endif //LIME_ERRORS_HPP