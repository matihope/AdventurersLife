#include <ResourceManager/ResourceManager.hpp>


ResourceManager& ResourceManager::get() {
    static ResourceManager instance;
    return instance;
}

const sf::Texture& ResourceManager::IgetTexture(const std::string& path) {
    ResourceManager& resourceManager = get();
    if(!resourceManager.m_textures.count(path)){
        resourceManager.m_textures[path] = std::make_unique<sf::Texture>();
        resourceManager.m_textures[path]->loadFromFile(path);
    }
    return *resourceManager.m_textures[path].get();
}

const sf::Texture& ResourceManager::getTexture(const std::string& path) {
    return get().IgetTexture(path);
}
