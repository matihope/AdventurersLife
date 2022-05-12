#include <Game/Game.hpp>
#include <iterator>
#include <iostream>

void Game::draw(sf::RenderTarget& target) {
    target.draw(sprites);
}

void Game::update(){
    m_dt = m_clock.restart().asSeconds();
    // std::cout << 1.f/m_dt << '\n';
    for(auto& updatable : m_updatables){
        updatable->update(m_dt);
    }
}

void Game::addUpdatable(std::shared_ptr<Updatable> updatable){
    m_updatables.push_back(std::move(updatable));
}
