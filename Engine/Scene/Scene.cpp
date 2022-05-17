#include <Game/Game.hpp>
#include <Scene/Scene.hpp>

void Scene::update(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->update(dt);
    }
}

void Scene::physicsUpdate(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->physicsUpdate(dt);
    }
}

void Scene::draw(sf::RenderTarget& target){
    target.draw(sprites);
}

void Scene::addUpdatable(std::shared_ptr<Updatable> updatable){
    updatable->addScene(this);
    updatable->ready();
    m_updatables.push_back(std::move(updatable));
}

void Scene::addGame(Game* game){
    m_game = game;
}

Game* Scene::getGame() const {
    return m_game;
}
