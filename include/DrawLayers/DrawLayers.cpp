#include <DrawLayers/DrawLayers.hpp>
#include <iterator>

void DrawLayers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for(auto it = m_background_sprites.begin(); it != m_background_sprites.end(); ++it) {
        for(auto& sprite : it->second){
            target.draw(*sprite, states);
        }
    }
}

void DrawLayers::addSprites(SpriteVector& sprites, uint drawOrder){

    // function usage example outside this class:

        // std::unique_ptr<TileMap> map = std::make_unique<TileMap>();
        // std::vector<std::unique_ptr<sf::Drawable>> sprites;
        // sprites.push_back(std::move(map));
        // game.addBackgroundSprites(sprites, 0);

    m_background_sprites[drawOrder].insert(
        m_background_sprites[drawOrder].end(),
        std::make_move_iterator(sprites.begin()),
        std::make_move_iterator(sprites.end())
    );
}

void DrawLayers::addSprite(SpritePointer sprite, uint drawOrder){
    m_background_sprites[drawOrder].push_back(std::move(sprite));
}
