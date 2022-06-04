#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class ResourceManager {
    private:
        ResourceManager() {};
        static ResourceManager& get();
        const sf::Texture& IgetTexture(const std::string& path);
        std::shared_ptr<sf::Font> IgetFont(const std::string& path);
        std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;

    public:
        ResourceManager(const ResourceManager&) = delete;
        static const sf::Texture& getTexture(const std::string& path);
};
