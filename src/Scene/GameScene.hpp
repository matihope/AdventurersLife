#pragma once
#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <TileMap/TileMap.hpp>
#include <Player/Player.hpp>

class GameScene : public Scene {
    private:
        Player* m_player;

    public:
        bool load();
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
};
