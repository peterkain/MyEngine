#include "Sandbox.h"
#include "GL/Mesh.h"
#include "GL/Shader.h"
#include "GL/ResourceManager.h"
#include "GL/Input.h"
#include "GL/TextureAtlas.h"
#include "TileMap.h"

#include <vector>
#include <glm/gtc/matrix_transform.hpp>

constexpr u8 tile_size{ 16 };

Sandbox::Sandbox(int w, int h, const char* title, bool fullscreen, engine::WindowInfo info)
    : Application{ w, h, title, fullscreen, info }
{
    camera.setup(0, 0, w, h, -1.f, 1.f, engine::CameraType::Orthographic, 1.f);
    camera.zoom_ortho_max(10.f);
    camera.zoom_ortho_steps(10);
    camera.speed(256.f);

    window->on_mousescroll([&](double offset_x, double offset_y)
        {
            camera.zoom_ortho(offset_y);
        }
    );
}

void Sandbox::init()
{
    engine::Texture::set_defaults("../res/textures/block.png");
    engine::Shader::set_path_prefix("../res/shaders/engine/");

    engine::RM::texture("atlas1", { "../res/textures/texture_atlas1.png", true, false, GL_CLAMP, GL_CLAMP });
    atlas = std::make_unique<engine::TextureAtlas>(engine::RM::texture("atlas1"), 16);

    engine::RM::shader("tilemap", { "position_uv_vs.glsl", "texture_atlas_fs.glsl" });

    std::vector<glm::mat4> models{ glm::scale(glm::mat4{1.}, glm::vec3{tile_size}) };
    engine::TileMap tilemap{ "../res/maps/tilemap.map" };
    tilemap.generate_textures();

    std::vector<engine::Vertex> vertices{
       {{ tile_size, tile_size, 0}, {tilemap.width(), tilemap.height()}},
       {{ tile_size,-tile_size, 0}, {tilemap.width(), 0.f}},
       {{-tile_size,-tile_size, 0}, {0.f, 0.f}},
       {{-tile_size, tile_size, 0}, {0.f, tilemap.height()}}
    };

    std::vector<u32> indices{
        0, 1, 2,
        2, 3, 0
    };

    engine::RM::mesh("rect", { vertices, indices });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	engine::RM::stored_render("renderTiles", [models, tilemap, this]
        (engine::Renderer& renderer, engine::Camera& camera)
		{
            auto mesh{ engine::RM::mesh("rect") };
            auto shader{ engine::RM::shader("tilemap") };
            auto texture{ engine::RM::texture("atlas1") };

            renderer.render_tiles({ shader, mesh, texture, camera.projection() * camera.view(), models,
                atlas->size(), static_cast<GLuint>(tilemap(0)) });
		}
	);

    engine::Renderer::set_mode(engine::Rendermode::Fill);
    window->clear_color({ .5f, .3f, .1f, 1.f });
    window->swap_interval(0);
}

void Sandbox::loop()
{
    window->clear(engine::WindowBuffer::Color);

    engine::RM::stored_render("renderTiles")->render(renderer, camera);
}

void Sandbox::process_input()
{
    if (input.key_pressed(GLFW_KEY_W))
    {
        camera.move(engine::CameraMovement::Down, window->dt());
    }
    if (input.key_pressed(GLFW_KEY_A))
    {
        camera.move(engine::CameraMovement::Right, window->dt());
    }
    if (input.key_pressed(GLFW_KEY_S))
    {
        camera.move(engine::CameraMovement::Up, window->dt());
    }
    if (input.key_pressed(GLFW_KEY_D))
    {
        camera.move(engine::CameraMovement::Left, window->dt());
    }
}
