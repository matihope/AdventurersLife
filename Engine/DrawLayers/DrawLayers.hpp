#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <GameObj/GameObj.hpp>

typedef std::shared_ptr<GameObj> SpritePointer;
typedef std::vector<SpritePointer> SpriteVector;

class DrawLayers : public GameObj {

    std::map<unsigned int, SpriteVector> m_background_sprites;

    public:
        DrawLayers(){};
        ~DrawLayers(){};
        void addSprites(SpriteVector&, unsigned int);
        void addSprite(SpritePointer, unsigned int);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
