#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "GL/Texture.h"
#include "Parameters.h"


namespace engine {

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

class Mesh
{
    friend class Renderer;
public:
    Mesh(Parameters<Mesh> params);

public:
    const std::vector<Vertex>& vertices() const
    {
        return _vertices;
    }

    const std::vector<u32>& indices() const
    {
        return _indices;
    }

private:
    void create();

private:
    std::vector<Vertex> _vertices;
    GLuint _vao, _vbo, _ebo;
    std::vector<u32> _indices;
    u32 count;
};


}
