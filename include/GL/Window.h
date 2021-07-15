#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include "GL/Color.h"
#include "GL/TimePoint.h"
#include "GL/Event.h"
#include "GL/Subscriber.h"
#include "Types.h"


namespace engine {

struct WindowInfo;

enum class WindowBuffer
{
	Color = GL_COLOR_BUFFER_BIT,
	Depth = GL_DEPTH_BUFFER_BIT,
	Stencil = GL_STENCIL_BUFFER_BIT
};

class Window
{
public:
    Window(int w, int h, const char* title, bool fullscreen);
    ~Window();

public:
	inline void swap_interval(int interval)  const { glfwSwapInterval(interval); };
	inline void clear_color(Color::GL color) const { glClearColor(color.r, color.g, color.b, color.a); }
	void clear(const WindowBuffer& buffer);
    void begin_frame();
	void end_frame();

    inline void on_resize(std::function<void()> f)    { _resize->add_subscriber(f); }
	inline void on_keyupdate(std::function<void()> f) { _keyupdate->add_subscriber(f); }
	inline void on_mousemove(std::function<void(double, double)> f)   { _mousemove->add_subscriber(f); }
	inline void on_mousescroll(std::function<void(double, double)> f) { _mousescroll->add_subscriber(f); }

	inline float dt() const { return _dt; }
	inline GLFWwindow* const get_window() const                        { return _window; }
    inline int width() const                                           { return _w; }
    inline int height() const                                          { return _h; }
	inline bool should_close() const                                   { return glfwWindowShouldClose(_window); }
    inline void viewport(GLint x, GLint y, GLsizei w, GLsizei h) const { glViewport(x, y, w, h); }

    inline void update_title(std::string title, bool append = false) const
    {
        glfwSetWindowTitle(_window, std::string((append ? _title : "") + title).c_str());
    }
public:
    static void use_info(WindowInfo info);

private:
    // GLFW-Callbacks
	inline static void size_cb(GLFWwindow* window, int w, int h)
	{
		Window* wnd{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
		wnd->_w = w;
		wnd->_h = h;
		glViewport(0, 0, w, h);
		_resize->publish();
	}

	inline static void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* wnd{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
		if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) 
		{
			glfwSetWindowShouldClose(wnd->_window, true);
		}
		_keyupdate->publish();
	}

	inline static void mouse_cb(GLFWwindow* window, double offset_x, double offset_y)
	{
		_mousemove->publish(offset_x, offset_y);
	}

	inline static void scroll_cb(GLFWwindow* window, double offset_x, double offset_y)
	{
		_mousescroll->publish(offset_x, offset_y);
	}

private:
    GLFWwindow* _window;
	float _last, _dt;
	std::string _title;
    int _w, _h;
	inline static std::unique_ptr<Event<>> _resize{ std::make_unique<Event<>>(static_cast<event_t>(EventType::WindowResize)) };
	inline static std::unique_ptr<Event<>> _keyupdate{ std::make_unique<Event<>>(static_cast<event_t>(EventType::KeyUpdate)) };
	inline static std::unique_ptr<Event<double, double>> _mousemove{ std::make_unique<Event<double, double>>(static_cast<event_t>(EventType::MouseMove)) };
	inline static std::unique_ptr<Event<double, double>> _mousescroll{ std::make_unique<Event<double, double>>(static_cast<event_t>(EventType::MouseScroll)) };
};

}
