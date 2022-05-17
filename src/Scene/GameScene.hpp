#pragma once
#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <TileMap/TileMap.hpp>

class GameScene : public Scene {
    std::shared_ptr<TileMap> m_tile_map;

    public:
        void addTileMap(std::shared_ptr<TileMap> tileMap);
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
};
