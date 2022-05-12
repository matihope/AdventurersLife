#include <TileMap/TileMap.hpp>
#include <iostream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    m_layers.draw(target, states);
}

bool TileMap::load(const std::string& mapFile){
    if(!m_map_data.load(mapFile)){
        std::cout << "Error loading map: " << mapFile << std::endl;
        return false;
    }

    for(int i = 0; i < m_map_data.data["tilesets"].size(); i++) {
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        texture->loadFromFile(m_map_data.data["tilesets"][i]["image"]);
        textures.push_back(std::move(texture));
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

            for(int k = 0; k < textures.size(); ++k){
                int firstId = m_map_data.data["tilesets"][k]["firstgid"];
                int tileCount = m_map_data.data["tilesets"][k]["tilecount"];
                if(firstId <= tileId && tileId <= firstId + tileCount){
                    tileId -= firstId;
                    auto tile = std::make_unique<sf::Sprite>();
                    int tileW = m_map_data.data["tilesets"][k]["tilewidth"];
                    int tileH = m_map_data.data["tilesets"][k]["tileheight"];
                    int textureW = m_map_data.data["tilesets"][k]["columns"];
                    tile->setTexture(*textures[k]);
                    tile->setTextureRect(sf::IntRect(
                        (tileId % textureW) * tileW,
                        (tileId / textureW) * tileH,
                        tileW,
                        tileH
                    ));
                    tile->setPosition(
                        (j % layerWidth) * tileW,
                        (j / layerWidth) * tileH
                    );
                    m_layers.addSprite(std::move(tile), i);
                    break;
                }
            }
        }
    }
    return true;
}
