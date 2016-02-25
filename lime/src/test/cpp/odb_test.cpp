#include <string>
#include <memory>
#include <lemon/io/io.hpp>
#include <lime/odb/odb.hpp>
#include <lemon/log/log.hpp>
#include <lemon/test/test.hpp>



using namespace lime::odb;
using namespace lemon::uuids;

auto &logger = lemon::log::get("test");

struct column_1
{
	std::string name;
	std::string text;

	~column_1()
	{
		//lemonI(logger,"~column_1");
	}
};

struct column_2
{
	double x;
	double y;

	~column_2()
	{
		//lemonI(logger, "~column_2");
	}
};

database db;

auto c1_id = db.newoid();
auto c2_id = db.newoid();

test_(create_object)
{
	db.register_column<column_1>(c1_id);
	db.register_column<column_2>(c2_id);

	auto o1 = db.create();

	o1->add_property(c1_id);
	o1->add_property(c2_id);

	db.garbagecollect(true);

	test_assert(db.create() == o1);
}

test_(create_table)
{
	auto test_table = db.create_table("test");

	test_assert(test_table->get_indexer_by_name(to_string(c1_id)) != nullptr);

	test_assert(test_table->get_indexer_by_name(to_string(c2_id)) != nullptr);

	for (int i = 0; i < 2000; i ++)
	{
		auto o1 = db.create();

		o1->add_property(c1_id);
		o1->add_property(c2_id);

		test_table->insert(o1);
	}
}

bench_(inser_remove)
{
	stop_timer();
	auto o = db.create();
	o->add_property(c1_id);
	o->add_property(c2_id);
	auto t = db.get_table("test");
	start_timer();

	for (int i = 0; i < N; i++)
	{
		t->insert(o);
		t->remove(o);
	}
}


bench_(garbagecollect)
{
	stop_timer();
	for (int i = 0; i < 100; i ++)
	{
		auto o = db.create();
		o->add_property(c1_id);
		o->add_property(c2_id);
	}

	start_timer();
	

	for (int i = 0; i < N; i++)
	{
		db.garbagecollect(true);
	}
	
}