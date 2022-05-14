#include <AnimatedSprite/AnimatedSprite.hpp>
#include <TileMap/TileMap.hpp>
#include <iostream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    m_layers.draw(target, states);
}

bool TileMap::load(const std::string& mapFile){
    m_tilemap_path = mapFile;
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
                animation.texture = *texture;
                for(auto& frame: tile["animation"]){
                    animation.frames.push_back(
                        {
                            uint(frame["duration"]),
                            m_tile_templates[int(frame["tileid"]) + fileTileId]->getTextureRect()
                        }
                    );
                }
                auto animated = std::make_shared<AnimatedSprite>();
                animated->addAnimation(animation, "base");
                animated->play("base");
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
            auto tile = std::make_shared<sf::Sprite>(getTileTemplate(tileId));
            if(m_is_animated[tileId]){
                // Some wild stuff going on here... but it works tho
                auto other = std::dynamic_pointer_cast<AnimatedSprite>(m_tile_templates[tileId]);
                auto animatedTile = std::make_shared<AnimatedSprite>(*other);
                m_updatables.push_back(animatedTile);
                tile = std::dynamic_pointer_cast<sf::Sprite>(animatedTile);
            }
            tile->setPosition( (j % layerWidth) * tileW, (j / layerWidth) * tileH );
            m_layers.addSprite(std::move(tile), i);

        }
    }
    return true;
}

sf::Sprite TileMap::getTileTemplate(uint id) const {
    return *m_tile_templates.at(id);
}

void TileMap::update(const float& dt){
    for(auto& updatable: m_updatables)
        updatable->update(dt);
}

bool TileMap::reload(){
    m_map_data.data.clear();
    m_layers = DrawLayers();
    m_textures.clear();
    m_tile_templates.clear();
    m_is_animated.clear();
    m_updatables.clear();
    return load(m_tilemap_path);
}
