/**
 *
 * @file     column
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_COLUMN_HPP
#define LIME_ODB_COLUMN_HPP
#include <vector>
#include <lemon/nocopy.hpp>
#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		class column : private lemon::nocopy
		{
		public:
			column(
				const oid & id,
				std::size_t nsize,
				void(*createf)(void*buff), 
				void(*deletef)(void*buff));


			std::size_t hashcode()
			{
				return _hashcode;
			}

			const oid & id() const
			{
				return _id;
			}

			object_property *create_property(object *obj);

			void close_property(object_property* proto) noexcept;

		private:
			void(*_createf)(void*buff);
			void(*_deletef)(void*buff);
			oid										_id;
			std::size_t								_hashcode;
			std::size_t								_size;
			std::vector<object_property*>			_cached;
		};
	}
}

#endif //LIME_ODB_COLUMN_HPP