#pragma once

#include "GL/Shader.h"
#include "GL/Texture.h"
#include "GL/TextureAtlas.h"
#include "GL/Mesh.h"
#include "GL/Renderer.h"
#include "GL/Logger.h"

#include <unordered_map>
#include <memory>
#include <sstream>

namespace engine
{
using RM = ResourceManager;
class ResourceManager
{
	static inline std::unordered_map<std::string, std::unique_ptr<Shader>> _shaders{};
	static inline std::unordered_map<std::string, std::unique_ptr<Texture>> _textures{};
    static inline std::unordered_map<std::string, std::unique_ptr<StoredRender>> _stored_renders{};
    static inline std::unordered_map<std::string, std::unique_ptr<Mesh>> _meshes{};

    ResourceManager() = default;

	template<class T>
	static T* const get(const std::unordered_map<std::string, std::unique_ptr<T>>& map, const std::string& name);

public:
	~ResourceManager();

	static inline void shader(const std::string& name, Parameters<Shader> info)
	{
		_shaders.insert({ name, std::make_unique<Shader>(info) });
	}

	static inline Shader* const shader(const std::string& name)
	{
		return get<Shader>(_shaders, name);
	}

	static inline void remove_shader(const std::string& name)
	{
		_shaders.erase(name);
	}

    static inline void clear_shaders()
	{
		_shaders.clear();
	}

	static inline void texture(const std::string& name, Parameters<Texture> info)
	{
		_textures.insert({ name, std::make_unique<Texture>(info) });
	}

	static inline Texture* const texture(const std::string& name)
	{
		return get<Texture>(_textures, name);
	}

	static inline void remove_texture(const std::string& name)
	{
        _textures.erase(name);
	}

    static inline void clear_textures()
	{
        _textures.clear();
	}

    static inline void mesh(const std::string& name, Parameters<Mesh> info)
    {
		_meshes.insert({ name, std::make_unique<Mesh>(info) });
    }

    static inline Mesh* const mesh(const std::string& name)
    {
		return get<Mesh>(_meshes, name);
    }

    static inline void remove_mesh(const std::string& name)
	{
        _meshes.erase(name);
	}

    static inline void clear_meshes()
	{
        _meshes.clear();
	}

    static inline void stored_render(const std::string& name, StoredRenderFun&& fun)
    {
		_stored_renders.insert({ name, std::make_unique<StoredRender>(fun) });
    }

    static inline StoredRender* const stored_render(const std::string& name)
    {
		return get<StoredRender>(_stored_renders, name);
    }

	static std::vector<StoredRender*> stored_renders(const std::string& names, const char delim = '&');

    static inline void remove_stored_render(const std::string& name)
	{
        _stored_renders.erase(name);
	}

	static inline void clear_stored_renders()
	{
        _stored_renders.clear();
	}

	static void clear();
};
}
