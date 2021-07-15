#pragma once

#include "GL/Mesh.h"
#include "GL/Shader.h"
#include "GL/Camera.h"
#include <memory>
#include <functional>
#include "Types.h"
#include "TileMap.h"

namespace engine {

enum class Rendermode {
	Line = GL_LINE,
	Fill = GL_FILL
};

struct RenderData
{
    Shader* shader;
    Mesh* mesh;
    Texture* texture;
    glm::mat4 proj_view;
    std::vector<glm::mat4> models;
};

struct RenderDataTiles : public RenderData
{
    float texture_size;
    GLuint tiledata_id;
};

class Renderer
{
public:
    Renderer();

public:
    void render_mesh(RenderData data);
    void render_tiles(RenderDataTiles data);

	inline void set_active_texture(u8 texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
	}

    inline static void set_mode(const Rendermode& mode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
    }
};


using StoredRenderFun = std::function<void(Renderer&, Camera&)>;

class StoredRender
{
public:
    StoredRender(StoredRenderFun f)
        : _func{ f }
    {  }

    inline void render(Renderer& r, Camera& c) const { _func(r, c); }

    inline StoredRender& operator=(StoredRenderFun&& f)
    {
        _func = std::move(f);
        return *this;
    }

private:
    StoredRenderFun _func;
};

}
