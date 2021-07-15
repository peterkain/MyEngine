#include "GL/Window.h"
#include "GL/WindowInfo.h"
#include "GL/Logger.h"

#include <iostream>

#ifdef _ENGINE_DEBUG
#include "GL/TimePoint.h"
#endif

namespace engine {

Window::Window(int w, int h, const char* title, bool fullscreen)
	: _title{ title }
    , _window{ nullptr }
    , _w{ w }
    , _h{ h }
    , _dt{ 0.f }
    , _last{ 0.f }
{
#ifdef _ENGINE_DEBUG
    TimePointMil timer{ "Window creation" };
	timer.time_point();
#endif
    if(Engine::is_initialized())
    {
        _window = glfwCreateWindow(_w, _h, _title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

        if(!_window)
            Logger::log("engine::Window\n\tWindow creation failed", Logger::Level::Error);

		glViewport(0, 0, _w, _h);

        glfwMakeContextCurrent(_window);

        glewExperimental = GL_TRUE;
        GLenum status{ glewInit() };
        if(status != GLEW_OK)
            Logger::log("engine::Window\n\tFailed to initialize GLEW", Logger::Level::Error);

		glfwSetWindowUserPointer(_window, this);
		glfwSetWindowSizeCallback(_window, Window::size_cb);
		glfwSetKeyCallback(_window, Window::key_cb);
        glfwSetCursorPosCallback(_window, Window::mouse_cb);
        glfwSetScrollCallback(_window, Window::scroll_cb);
    }
#ifdef _ENGINE_DEBUG
	timer.time_point();
	Logger::log(timer.str("ms"));
#endif
}


Window::~Window()
{
    glfwDestroyWindow(_window);
}


void Window::clear(const WindowBuffer& buffer)
{
    glClear(static_cast<GLenum>(buffer));
}


void Window::begin_frame()
{
    float curr{ (float)glfwGetTime() };
    _dt = curr - _last;
    _last = curr;
}


void Window::end_frame()
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
}


void Window::use_info(WindowInfo info)
{
    if(Engine::is_initialized())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.major_version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minor_version);
        glfwWindowHint(GLFW_SAMPLES, info.samples);
        glfwWindowHint(GLFW_RESIZABLE, info.resizable);
    }
}

}
