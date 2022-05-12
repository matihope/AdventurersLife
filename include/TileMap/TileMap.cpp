#include <TileMap/TileMap.hpp>
#include <iostream>
#include <AnimatedSprite/AnimatedSprite.hpp>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    m_layers.draw(target, states);
}

bool TileMap::load(const std::string& mapFile){
    if(!m_map_data.load(mapFile)){
        std::cout << "Error loading map: " << mapFile << std::endl;
        return false;
    }

    uint tileW = m_map_data.data["tilewidth"];
    uint tileH = m_map_data.data["tileheight"];
    for(int i = 0; i < m_map_data.data["tilesets"].size(); i++) {

        // load texture from file
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        texture->loadFromFile(m_map_data.data["tilesets"][i]["image"]);

        // create presets
        uint fileTileId = m_map_data.data["tilesets"][i]["firstgid"];
        uint tilesX = m_map_data.data["tilesets"][i]["columns"];
        uint tilesY = int(m_map_data.data["tilesets"][i]["tilecount"]) / tilesX;
        for(int y = 0; y < tilesY; ++y){
            for(int x = 0; x < tilesX; ++x){
                auto tile_template = std::make_shared<sf::Sprite>();
                tile_template->setTexture(*texture);
                tile_template->setTextureRect(sf::IntRect(x * tileW, y * tileH, tileW, tileH));
                m_tile_templates[fileTileId + x + y * tilesX] = tile_template;
            }
        }

        // create all animated sprites
        if(m_map_data.data["tilesets"][i].contains("tiles")){
            for(auto tile: m_map_data.data["tilesets"][i]["tiles"]){
                if(!tile.contains("animation"))
                    continue;


                Animation animation;
                for(auto& frame: tile["animation"]){
                    animation.push_back(
                        {
                            uint(frame["duration"]),
                            m_tile_templates[int(frame["tileid"]) + fileTileId]->getTextureRect()
                        }
                    );
                }
                auto animated = std::make_shared<AnimatedSprite>();
                m_tile_templates[int(tile["id"]) + fileTileId] = animated;
                m_is_animated[int(tile["id"]) + fileTileId] = true;
            }
        }

        m_textures.push_back(std::move(texture));
    }
    // layers
    for(int i = 0; i < m_map_data.data["layers"].size(); ++i){
        if(m_map_data.data["layers"][i]["type"] != "tilelayer")
            continue;
        int layerWidth = m_map_data.data["layers"][i]["width"];
        int layerHeight = m_map_data.data["layers"][i]["height"];

        // individual tiles
        for(int j = 0; j < m_map_data.data["layers"][i]["data"].size(); ++j){
            int tileId = m_map_data.data["layers"][i]["data"][j];

            // skip if empty
            if(tileId == 0)
                continue;

            // copy tile from template and locate it correctly
            auto tile = std::make_unique<sf::Sprite>(*m_tile_templates[tileId]);
            tile->setPosition(
                (j % layerWidth) * tileW,
                (j / layerWidth) * tileH
            );
            m_layers.addSprite(std::move(tile), i);
            // if(m_is_animated[tileId])

        }
    }
    return true;
}

sf::Sprite TileMap::getTileTemplate(uint id) const {
    return *m_tile_templates.at(id);
}

void TileMap::update(float dt){
    for(auto& updatable: m_updatables)
        updatable->update(dt);
}
