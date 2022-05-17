#include <Game/Game.hpp>
#include <Scene/GameScene.hpp>

void GameScene::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_tile_map->reload();
    }
    Scene::update(dt);
}

void GameScene::draw(sf::RenderTarget& target) {
    Scene::draw(target);
}

void GameScene::addTileMap(std::shared_ptr<TileMap> tileMap) {
    m_tile_map = tileMap;
    addUpdatable(tileMap);
    sprites.addSprite(tileMap, 0);
}
