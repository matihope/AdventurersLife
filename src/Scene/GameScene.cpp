#include <Game/Game.hpp>
#include <Scene/GameScene.hpp>
#include <Player/Player.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <algorithm>

void GameScene::update(const float& dt) {
    Scene::update(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_tile_map->reload();
    }
}

void GameScene::draw(sf::RenderTarget& target) {
    Scene::draw(target);
    // std::vector<std::shared_ptr<WorldEntity>> ySort;
    // for(auto& p : getTileMap()->getYSortLayerTiles())
    //     ySort.push_back(p);
    // ySort.push_back(m_player);
    // std::sort(ySort.begin(), ySort.end(), [&](const auto& a, const auto& b){
    //     return a->getPosition().y < b->getPosition().y;
    // });
    // for(auto& p: ySort) {
    //     target.draw(*p);
    // }
}

bool GameScene::load() {
    auto map = std::make_unique<TileMap>();
    if(!map->loadLDtkMap("../worlds/world_test.ldtk"))
        std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
    else
    addTileMap(map);

    m_player = std::make_unique<Player>();
    // sprites.addSprite(m_player, 1);
    addUpdatable(m_player);
    return true;
}

std::shared_ptr<TileMap> GameScene::getTileMap() const {
    return m_tile_map;
}
