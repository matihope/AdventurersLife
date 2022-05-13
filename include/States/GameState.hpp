#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <States/State.hpp>
#include <TileMap/TileMap.hpp>

class GameState : public State {
    std::shared_ptr<TileMap> m_tile_map;

    public:
        void addTileMap(std::shared_ptr<TileMap> tileMap);
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
        void kill() override;
};

#endif
