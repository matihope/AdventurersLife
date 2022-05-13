#include <States/GameState.hpp>

void GameState::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_tile_map->reload();
    }
    State::update(dt);
}

void GameState::draw(sf::RenderTarget& target) {
    State::draw(target);
}

void GameState::kill(){
    // empty
}

void GameState::addTileMap(std::shared_ptr<TileMap> tileMap){
    m_tile_map = tileMap;
    addUpdatable(tileMap);
    sprites.addSprite(tileMap, 0);
}
