#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <DrawLayers/DrawLayers.hpp>

class TileMap : public sf::Drawable {
    JsonBridge m_map_data;
    DrawLayers m_layers;
    std::vector<std::unique_ptr<sf::Texture>> textures;

    public:
        bool load(const std::string& mapFile);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
