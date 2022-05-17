#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include <Contexts/Context.hpp>
#include <TileMap/TileMap.hpp>

class GameContext : public Context {
    std::shared_ptr<TileMap> m_tile_map;

    public:
        void addTileMap(std::shared_ptr<TileMap> tileMap);
        void draw(sf::RenderTarget& target);
        void update(const float& dt);
};

#endif
