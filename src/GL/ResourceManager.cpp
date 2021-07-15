#include "GL/ResourceManager.h"

namespace engine
{
    ResourceManager::~ResourceManager()
    {
        clear();
    }


    std::vector<StoredRender*> ResourceManager::stored_renders(const std::string& names, const char delim)
    {
        std::stringstream ss;
        std::string buffer;
        std::vector<StoredRender*> srs;
        srs.reserve(2);

        ss << names;
        while (std::getline(ss, buffer, delim))
        {
#ifdef _ENGINE_DEBUG
            Logger::log("[RM::stored_renders] Getting '" + buffer + '\'', Logger::Level::Debug);
#endif
            srs.emplace_back(stored_render(buffer));
        }

        return srs;
    }


    template<class T>
    T* const ResourceManager::get(const std::unordered_map<std::string, std::unique_ptr<T>>& map, const std::string& name)
    {
#ifdef _ENGINE_DEBUG
        auto result{ map.find(name) };
        if (result == map.end())
        {
            Logger::log("[RM::get] '" + name + "' not found", Logger::Level::Error);
            return nullptr;
        }
        return result->second.get();
#else
        return map.find(name)->second.get();
#endif
    }


    void ResourceManager::clear()
    {
#ifdef _ENGINE_DEBUG
        Logger::log("engine::ResourceManager freeing Resources...", Logger::Level::Debug);
#endif
        clear_meshes();
        clear_shaders();
        clear_textures();
        clear_stored_renders();
    }

template Shader* const ResourceManager::get<Shader>(const std::unordered_map<std::string, std::unique_ptr<Shader>>&, const std::string&);
template Mesh* const ResourceManager::get<Mesh>(const std::unordered_map<std::string, std::unique_ptr<Mesh>>&, const std::string&);
template Texture* const ResourceManager::get<Texture>(const std::unordered_map<std::string, std::unique_ptr<Texture>>&, const std::string&);
template StoredRender* const ResourceManager::get<StoredRender>(const std::unordered_map<std::string, std::unique_ptr<StoredRender>>&, const std::string&);
}
