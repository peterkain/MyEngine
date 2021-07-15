#include "GL/Engine.h"
#include "GL/Logger.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace engine {

Graphics_Api Engine::_api;
bool Engine::_is_initialized = false;


void Engine::init()
{
    if(!_is_initialized)
    {
        if(!glfwInit())
            Logger::log("engine::Engine\n\tFailed to initialize GLFW", Logger::Level::Error);

#ifdef _ENGINE_OPENGL
		init_gl();
#elif defined _ENGINE_VULKAN
		init_vk();
#else 
#define _ENGINE_OPENGL
		Logger::log("Using Default API: OpenGL");
		init_gl();
#endif
        _is_initialized = true;
    } else
        Logger::log("engine::Engine\n\tThe method Engine::init() must only be called once", Logger::Level::Error);
}

/*
void Engine::enable_debug() 
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Engine::ogl_messagecb, 0); 
}


void GLAPIENTRY Engine::gl_messagecb(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* msg, const void* userparam)
{
    static std::stringstream ss;
    ss.clear();
    std::string sseverity = severity == 0x9148 ? "High" :
                            severity == 0x9147 ? "Medium" :
                            severity == 0x9146 ? "Low" : "Info";
    ss << "[OpenGL MSG_Callback]: " << msg << "\nSeverity: " << sseverity;
    Logger::log(ss.str(), sseverity[0] != 'I' ? Logger::Severity::Warning : Logger::Severity::Info);
}
*/

void Engine::terminate()
{
    glfwTerminate();
}


void Engine::init_gl()
{
    _api = Graphics_Api::OpenGL;
    Logger::log("Initializing OpenGL...");
}


void Engine::init_vk()
{
    _api = Graphics_Api::Vulkan;
    Logger::log("Initializing Vulkan...");
}

}
