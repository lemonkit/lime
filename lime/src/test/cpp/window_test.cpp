#include <thread>
#include <lemon/test/test.hpp>
#include <lime/display.hpp>

test_(create_window)
{
	lime::window win("test",800,600);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	win.resize(400, 300);

	std::this_thread::sleep_for(std::chrono::seconds(1));
}