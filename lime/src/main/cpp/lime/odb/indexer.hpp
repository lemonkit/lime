/**
 *
 * @file     indexer
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/24
 */
#ifndef LIME_ODB_INDEXER_HPP
#define LIME_ODB_INDEXER_HPP

#include <unordered_map>
#include <lime/odb/database.hpp>

namespace lime{
	namespace odb{

		class indexer : private lemon::nocopy
		{
		public:
			indexer(column &cln,const std::string &name) noexcept;

			const std::string & name() const noexcept
			{
				return _name;
			}

			std::size_t hashcode() const noexcept
			{
				return _hashcode;
			}

			column * get_column() const
			{
				return &_column;
			}

			virtual void update(object_property *pro) = 0;
			virtual void remove(object_property *pro) = 0;

		private:
			column								&_column;
			std::string							_name;
			std::size_t							_hashcode;
		};

		class object_indexer : public indexer
		{
		public:
			using indexer::indexer;

			const std::unordered_map<oid, object_property*>& objects() const
			{
				return _indexer;
			}

		private:
			
			void update(object_property *pro) final;
			void remove(object_property *pro) final;

		private:
			std::unordered_map<oid, object_property*> _indexer;
		};
	}
}

#endif //LIME_ODB_INDEXER_HPP