#include <Game/Game.hpp>
#include <Scene/Scene.hpp>
#include <list>

void Scene::cleanEntities() {
    for(auto& layer : m_entity_pool){

        for(auto it = layer.second.begin(); it != layer.second.end(); it++){
            WorldEntity* entity = it->get();
            if(entity->isDying()) {
                entity->_kill();
                it = layer.second.erase(it);
            }
        }
    }
}

void Scene::update(const float& dt){
    for(const auto& layer : m_entity_pool){
        for(auto& entity : layer.second)
            entity->update(dt);
    }
}

void Scene::physicsUpdate(const float& dt){
    for(const auto& layer : m_entity_pool){
        for(auto& entity : layer.second)
            entity->physicsUpdate(dt);
    }
}

void Scene::draw(sf::RenderTarget& target){
    for(const auto& layer : m_entity_pool){
        for(auto& entity : layer.second)
            target.draw(*entity);
    }
}

void Scene::addEntity(std::unique_ptr<WorldEntity> entity, unsigned int drawOrder){
    entity->addScene(this);
    entity->ready();
    m_entity_pool[drawOrder].push_back(std::move(entity));
}

void Scene::addGame(Game* game){
    m_game = game;
}

Game* Scene::getGame() const {
    return m_game;
}
