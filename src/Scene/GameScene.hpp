#pragma once
#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <TileMap/TileMap.hpp>
#include <Player/Player.hpp>

class GameScene : public Scene {
    std::shared_ptr<TileMap> m_tile_map;
    std::shared_ptr<Player> m_player;

    public:
        void load();
        void addTileMap(std::shared_ptr<TileMap> tileMap);
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
        std::shared_ptr<TileMap> getTileMap() const;

};
