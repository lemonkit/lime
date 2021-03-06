#ifndef LEMON_IO_ERRORS_HPP
#define LEMON_IO_ERRORS_HPP

#include <string>
#include <system_error>

namespace lime {
	enum class errc
	{
		resize_error = 1
	};

	class lime_error_category : public std::error_category
	{
	private:

		const char *name() const throw()
		{
			return "lime::lime_error_category";
		}

		std::string message(int val) const
		{
			switch ((errc)val)
			{
			case errc::resize_error:
				return "can't resize the window or rend element";
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
		static lime_error_category io_error_category;

		return std::error_code(static_cast<int>(err), io_error_category);
	}

}

namespace std {
	template<> struct is_error_code_enum<::lime::errc> : true_type {};
}
#endif //LEMON_IO_ERRORS_HPP
