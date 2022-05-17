#include <pch.h>
#include <Contexts/Context.hpp>
#include <Game/Game.hpp>

void Context::update(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->update(dt);
    }
}

void Context::physicsUpdate(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->physicsUpdate(dt);
    }
}

void Context::draw(sf::RenderTarget& target){
    target.draw(sprites);
}

void Context::addUpdatable(std::shared_ptr<Updatable> updatable){
    updatable->addContext(this);
    updatable->ready();
    m_updatables.push_back(std::move(updatable));
}

void Context::addGame(Game* game){
    m_game = game;
}

Game* Context::getGame() const {
    return m_game;
}
