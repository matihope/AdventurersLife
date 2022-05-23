#include <Game/Game.hpp>
#include <Scene/GameScene.hpp>
#include <Player/Player.hpp>
#include <algorithm>

void GameScene::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_tile_map->reload();
    }
    Scene::update(dt);
}

void GameScene::draw(sf::RenderTarget& target) {
    Scene::draw(target);
    std::vector<std::pair<std::shared_ptr<sf::Transformable>, std::shared_ptr<sf::Drawable>>> ySort;
    for(auto& p : getTileMap()->getYSortLayerTiles())
        ySort.push_back({p, p});
    ySort.push_back({m_player, m_player});
    std::sort(ySort.begin(), ySort.end(), [&](const auto& a, const auto& b){
        return a.first->getPosition().y < b.first->getPosition().y;
    });
    for(auto& p: ySort) {
        target.draw(*p.second);
    }
}

void GameScene::addTileMap(std::shared_ptr<TileMap> tileMap) {
    m_tile_map = tileMap;
    addUpdatable(tileMap);
    sprites.addSprite(tileMap, 0);
}

void GameScene::load() {
    auto map = std::make_shared<TileMap>();
    if(!map->load("../worlds/world.json"))
        std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
    else
    addTileMap(map);

    m_player = std::make_shared<Player>();
    // sprites.addSprite(m_player, 1);
    addUpdatable(m_player);
}

std::shared_ptr<TileMap> GameScene::getTileMap() const {
    return m_tile_map;
}
