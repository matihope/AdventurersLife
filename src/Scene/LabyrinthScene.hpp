#pragma once
#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <PlayerLabyrinth/Player.hpp>
#include <Tile/Tile.hpp>


class LabyrinthScene : public Scene {
    std::vector<std::shared_ptr<Tile>> m_tiles;
    std::shared_ptr<PlayerL> m_player;

    public:
        void draw(sf::RenderTarget& target);
        void load();
        std::vector<std::shared_ptr<Tile>>& getTiles();

};
