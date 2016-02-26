#ifndef LIME_ODB_ERRORS_HPP
#define LIME_ODB_ERRORS_HPP

#include <string>
#include <system_error>

namespace lime {namespace odb{
	enum class errc
	{
		duplicate_object_oid = 1,
		
		duplicate_column_oid,
		
		unknown_column_oid, 
		
		duplicate_table_name,
		
		duplicate_insert,

		duplicate_add_child
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
			case errc::duplicate_object_oid:
				return "duplicate object name";
			case errc::duplicate_column_oid:
				return "duplicate column name";
			case errc::unknown_column_oid:
				return "unknown column indicate by oid";
			case errc::duplicate_insert:
				return "insert object more than once";
			case errc::duplicate_table_name:
				return "duplicate table name";
			case errc::duplicate_add_child:
				return "duplicate insert child";
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

}}

namespace std {
	template<> struct is_error_code_enum<::lime::odb::errc> : true_type {};
}
#endif //LIME_ERRORS_HPP