#pragma once

#include "GL/Application.h"
#include "GL/Renderer.h"
#include "GL/WindowInfo.h"
#include "GL/Camera.h"
#include "GL/SplitScreen.h"

#include <memory>

class Sandbox : public engine::Application
{
    std::unique_ptr<engine::TextureAtlas> atlas;
public:
    Sandbox(int w, int h, const char* title, bool fullscreen, engine::WindowInfo info);

    virtual void init() override;
    virtual void loop() override;
    virtual void process_input() override;
};
