#ifndef LIME_ECS_ERRORS_HPP
#define LIME_ECS_ERRORS_HPP

#include <string>
#include <system_error>

namespace lime { namespace ecs {
        enum class errc
        {
			unknown_component_type = 1,duplicate_column_name, invalid_component,invalid_entity,already_exists
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
                case errc::unknown_component_type:
                    return "unknown component type";
				case errc::invalid_component:
					return "the component can't be handled by current database ";
				case errc::invalid_entity:
					return "the entity can't be handled by current database ";
				case errc::already_exists:
					return "the entity already created ";
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
    template<> struct is_error_code_enum<::lime::ecs::errc> : true_type {};
}
#endif //LEMON_IO_ERRORS_HPP