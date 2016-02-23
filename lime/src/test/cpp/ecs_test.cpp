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

database db;
auto cln1 = database::newid();
auto cln2 = database::newid();
auto o1 = db.create();

test_(ecs){

	o1->garbage_collect_mark();
	
	db.create_column<colunm_one>(cln1);
	db.create_column<colunm_two>(cln2);

	o1->set(cln1);
	o1->set(cln2);

	test_assert(o1->get(cln1) != nullptr);
	test_assert(o1->get(cln2) != nullptr);

	auto c = o1->get<colunm_one>(cln1);

	c->name = "hello world";
	c->text = "test column";

	test_assert(c == o1->get<colunm_one>(cln1));

	c = o1->get<colunm_one>(cln1);

	test_assert(c->name == "hello world");

	test_assert(c->text == "test column");

	for(auto & column : db.colunms())
	{
		for(auto & row : column.second->rows())
		{
			if(row.first == cln1)
			{
				c = row.second->get<colunm_one>();

				c->name = "hello 2";
			}
		}
	}

	for (auto i = 0; i < 10000; i++)
	{
		auto o = db.create();

		o->set(cln1);
		o->set(cln2);

		o1->add_child(o);

		test_assert(o == db.get(o->id()));
	}
}



bench_(get_component)
{
	for (int i = 0; i < N; i ++)
	{
		o1->get(cln2);
	}
}

bench_(visiable)
{
	for (int i = 0; i < N; i++)
	{
		o1->visiable(true);
		o1->visiable(false);
	}
}

bench_(garbage_collection)
{
	stop_timer();
	for (auto i = 0; i < 100; i++)
	{
		auto o = db.create();

		o->set(cln1);
		o->set(cln2);
	}
	start_timer();

	for (int i = 0; i < N; i ++)
	{
		db.garbage_collect();
	}
}