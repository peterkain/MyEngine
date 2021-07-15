#pragma once

#include "GL/Window.h"
#include "GL/Renderer.h"
#include "GL/Input.h"
#include "GL/Camera.h"
#include <memory>

namespace engine {

class Application
{
public:
    Application(int w, int h, const char* title, bool fullscreen, const WindowInfo& info);
	virtual ~Application();

	void run();

protected:
	virtual void init() = 0;
	virtual void loop() = 0;
	virtual void process_input() = 0;

    std::unique_ptr<Window> window;
	Input input;
	Camera camera;
	Renderer renderer;
};

}
