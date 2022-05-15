#include <Contexts/Context.hpp>

void Context::update(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->update(dt);
    }
}

void Context::draw(sf::RenderTarget& target){
    target.draw(sprites);
}

void Context::addUpdatable(std::shared_ptr<Updatable> updatable){
    m_updatables.push_back(std::move(updatable));
}

void Context::addGame(Game* game){
    m_game = game;
}
