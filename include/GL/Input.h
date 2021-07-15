#pragma once
#include "GL/Window.h"

namespace engine {
class Input
{
	friend class Application;

	GLFWwindow* _window;

	Input() : _window{ nullptr } {};
	inline void set_window(GLFWwindow* window) { _window = window; }
public:
	inline bool key_pressed(int key) { return glfwGetKey(_window, key) == GLFW_PRESS; }
	inline bool key_released(int key) { return glfwGetKey(_window, key) == GLFW_RELEASE; }
};
}