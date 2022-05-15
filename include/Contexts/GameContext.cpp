#include <Game/Game.hpp>
#include <Contexts/GameContext.hpp>

void GameContext::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_tile_map->reload();
    }
    Context::update(dt);
}

void GameContext::draw(sf::RenderTarget& target) {
    Context::draw(target);
}

void GameContext::addTileMap(std::shared_ptr<TileMap> tileMap) {
    m_tile_map = tileMap;
    addUpdatable(tileMap);
    sprites.addSprite(tileMap, 0);
}
