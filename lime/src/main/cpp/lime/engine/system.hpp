/**
 *
 * @file     system
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/02/25
 */
#ifndef LIME_ENGINE_SYSTEM_HPP
#define LIME_ENGINE_SYSTEM_HPP
#include <lime/odb/odb.hpp>

namespace lime {

	using sid = lemon::uuids::uuid;

	class system : private lemon::nocopy
	{

	public:

		virtual ~ system(){}
		virtual void update(odb::database &db) = 0;

		const sid & id() const
		{
			return _id;
		}

		std::size_t hashcode() const
		{
			return _hashcode;
		}

	protected:

		system(const sid & id):_id(id)
		{
			std::hash<sid> hasher;

			_hashcode = hasher(id);
		}

		

	private:
		sid						_id;
		std::size_t				_hashcode;
	};
}

#endif //LIME_ENGINE_SYSTEM_HPP