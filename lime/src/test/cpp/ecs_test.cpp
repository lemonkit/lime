#include <lemon/io/io.hpp>
#include <lemon/log/log.hpp>
#include <lemon/test/test.hpp>
#include <lime/ecs/ecs.hpp>
#include <string>
#include <memory>

using namespace lemon::io;
using namespace lime::ecs;
auto &logger = lemon::log::get("test");


struct colunm_one 
{
	std::string name;
	std::string text;
};

struct colunm_two 
{
	double x;
	double y;
};

test_(ecs){
	database db;

	auto o1 = &db.create();

	auto cln1 = database::newid();
	auto cln2 = database::newid();

	db.create_column<colunm_one>(cln1);
	db.create_column<colunm_two>(cln2);

	o1->set(cln1);
	o1->set(cln2);

	test_assert(o1->has(cln1));
	test_assert(o1->has(cln2));

	auto c = &o1->get<colunm_one>(cln1);

	c->name = "hello world";
	c->text = "test column";

	test_assert(c == &o1->get<colunm_one>(cln1));

	c = &o1->get<colunm_one>(cln1);

	test_assert(c->name == "hello world");

	test_assert(c->text == "test column");

	for(auto & column : db.colunms())
	{
		for(auto & row : column.second->rows())
		{
			if(row.first == cln1)
			{
				c = &row.second->get<colunm_one>();

				c->name = "hello 2";
			}
		}
	}
}