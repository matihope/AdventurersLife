#ifndef TILEMAP_H
#define TILEMAP_H
#include <JsonBridge/JsonBridge.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <Updatable/Updatable.hpp>

class TileMap : public sf::Drawable, public Updatable {
    std::string m_tilemap_path;
    JsonBridge m_map_data;
    DrawLayers m_layers;
    std::vector<std::unique_ptr<sf::Texture>> m_textures;
    std::map<uint, std::shared_ptr<sf::Sprite>> m_tile_templates;
    std::map<uint, bool> m_is_animated;
    std::vector<std::shared_ptr<Updatable>> m_updatables;

    public:
        bool load(const std::string& mapFile);
        bool reload();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite getTileTemplate(uint id) const;
        void update(const float& dt) override;
        void ready() override {};
};

#endif
