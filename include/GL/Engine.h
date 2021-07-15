#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#pragma once

#if defined _WIN32
#define _ENGINE_WINDOWS
#elif defined __linux__ || defined __linux || defined linux
#define _ENGINE_LINUX
#elif defined __APPLE__ || defined __MACH__
#define _ENGINE_APPLE
#else
#error "Unsupported Operating System!"
#endif

#include <GL/glew.h>

#include <memory>
#include <sstream>
#include "GL/Logger.h"


namespace engine {

enum class Graphics_Api
{
    OpenGL,
    Vulkan
};


class Engine
{
public:
    static void init();
    static void terminate();
    //static void enable_debug();

public:
	inline static bool is_initialized() { return _is_initialized; }
    inline static Graphics_Api used_api() { return _api; }

private:
    inline static void init_gl();
    inline static void init_vk();

/*private:
    static void GLAPIENTRY gl_messagecb(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* msg, const void* userparam);*/

private:
    static Graphics_Api _api;
    static bool _is_initialized;
};

}

#endif
