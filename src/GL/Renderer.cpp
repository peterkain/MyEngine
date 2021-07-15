#include "GL/Renderer.h"
#include "GL/Logger.h"
#include "GL/TextureAtlas.h"

#include <glm/gtc/matrix_transform.hpp>


namespace engine {

Renderer::Renderer()
{
}


void Renderer::render_mesh(RenderData data)
{
    data.shader->use();

    set_active_texture(0);
    glBindTexture(GL_TEXTURE_2D, data.texture->id());

    data.shader->set_mat4("u_projection_view", data.proj_view);
    
    glBindVertexArray(data.mesh->_vao);
    for (const auto& model : data.models)
    {
        data.shader->set_mat4("u_model", model);
        glDrawElements(GL_TRIANGLES, data.mesh->count, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    Shader::use_none();
}


void Renderer::render_tiles(RenderDataTiles data)
{
    data.shader->use();

    data.shader->set_int("TextureAtlas", 0);
    data.shader->set_int("TileData", 1);

    data.shader->set_mat4("u_projection_view", data.proj_view);

    data.shader->set_mat4("u_model", data.models[0]);
    data.shader->set_float("u_texture_size", data.texture_size);

    set_active_texture(0);
    glBindTexture(GL_TEXTURE_2D, data.texture->id());

    set_active_texture(1);
    glBindTexture(GL_TEXTURE_2D, data.tiledata_id);

    glBindVertexArray(data.mesh->_vao);

    glDrawElements(GL_TRIANGLES, data.mesh->count, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    Shader::use_none();
}

}
