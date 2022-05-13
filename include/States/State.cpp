#include <States/State.hpp>

void State::update(const float& dt){
    for(auto& updatable : m_updatables){
        updatable->update(dt);
    }
}

void State::draw(sf::RenderTarget& target){
    target.draw(sprites);
}

void State::addUpdatable(std::shared_ptr<Updatable> updatable){
    m_updatables.push_back(std::move(updatable));
}
