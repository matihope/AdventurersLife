#ifndef DRAWLAYERS_H
#define DRAWLAYERS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

typedef std::shared_ptr<sf::Drawable> SpritePointer;
typedef std::vector<SpritePointer> SpriteVector;

class DrawLayers : public sf::Drawable, sf::Transformable {

    std::map<uint, SpriteVector> m_background_sprites;

    public:
        DrawLayers(){};
        ~DrawLayers(){};
        void addSprites(SpriteVector&, uint);
        void addSprite(SpritePointer, uint);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
