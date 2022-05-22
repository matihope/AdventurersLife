#pragma once
#include <SFML/Graphics.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <Updatable/Updatable.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <Tile/Tile.hpp>
#include <map>

class TileMap : public sf::Drawable, public Updatable {
    std::string m_tilemap_path;
    JsonBridge m_map_data;
    DrawLayers m_layers;
    std::map<unsigned int, Tile> m_tile_templates;
    std::vector<std::shared_ptr<sf::Texture>> m_textures;
    std::vector<std::shared_ptr<Updatable>> m_updatables;
    std::vector<std::shared_ptr<Tile>> m_collidable_tiles;

    public:
        bool load(const std::string& mapFile);
        bool reload();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Tile getTileTemplate(unsigned int id) const;
        void update(const float& dt) override;
        void ready() override {};
        std::vector<std::shared_ptr<Tile>>& getCollidableTiles();
};
