/**
 *
 * @file     property
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_PROPERTY_HPP
#define LIME_ODB_PROPERTY_HPP

#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		class object_property : private lemon::nocopy
		{
		public:
			friend class column;
			friend class database;
		public:

			object_property(column & cln) noexcept;

			std::size_t hashcode() const;

			const oid & id() const;

			const object* get_object()
			{
				return _obj;
			}

			column* get_column() const
			{
				return &_column;
			}

		private:

			void reset(object * obj) noexcept;

			void close() noexcept;

			void * buff() noexcept
			{
				return _buff;
			}

		private:
			object				*_obj;
			column				&_column;
			oid					_id;
			std::size_t			_hashcode;
			char				_buff[1];
		};
	}
}

#endif //LIME_ODB_PROPERTY_HPP