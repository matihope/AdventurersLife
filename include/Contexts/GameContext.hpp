#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include <SFML/Graphics.hpp>
#include <Contexts/Context.hpp>
#include <TileMap/TileMap.hpp>

class GameState : public Context {
    std::shared_ptr<TileMap> m_tile_map;

    public:
        void addTileMap(std::shared_ptr<TileMap> tileMap);
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
        void kill() override;
};

#endif
