#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

typedef std::shared_ptr<sf::Drawable> SpritePointer;
typedef std::vector<SpritePointer> SpriteVector;

class DrawLayers : public sf::Drawable, sf::Transformable {

    std::map<unsigned int, SpriteVector> m_background_sprites;

    public:
        DrawLayers(){};
        ~DrawLayers(){};
        void addSprites(SpriteVector&, unsigned int);
        void addSprite(SpritePointer, unsigned int);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
