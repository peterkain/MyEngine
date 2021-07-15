#include "GL/Application.h"
#include "GL/Engine.h"

#include "GL/WindowInfo.h"

namespace engine {

Application::Application(int w, int h, const char* title, bool fullscreen, const WindowInfo& info) :
	camera{}, renderer{}
{
	Engine::init();
    Window::use_info(info);
	window = std::make_unique<Window>(w, h, title, fullscreen);
	input.set_window(window->get_window());
}

void Application::run()
{
#ifdef _ENGINE_DEBUG
	TimePointMil tp{ "init()" };
	tp.time_point();
#endif
	init();
#ifdef _ENGINE_DEBUG
	tp.time_point();
	Logger::log(tp.str("ms"));
#endif
	while (!window->should_close())
	{
		window->begin_frame();

		loop();
		process_input();

		window->end_frame();
	}
}

Application::~Application()
{
	Engine::terminate();
}

}
