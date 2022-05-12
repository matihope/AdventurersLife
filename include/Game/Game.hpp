#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <iostream>

class Game {

    public:
        DrawLayers sprites;
        void draw(sf::RenderTarget&);

        void update();
        void physicsUpdate();
};
#endif
