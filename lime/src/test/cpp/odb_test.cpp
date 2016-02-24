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
		lemonI(logger,"~column_1");
	}
};

struct column_2
{
	double x;
	double y;

	~column_2()
	{
		lemonI(logger, "~column_2");
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

	while (!db.garbagecollect());

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

bench_(garbagecollect)
{
	for (int i = 0; i < N; i ++)
	{
		while (!db.garbagecollect());
	}
}