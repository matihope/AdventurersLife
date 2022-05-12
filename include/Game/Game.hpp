#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>
#include <iostream>

class Game {
    float m_dt = 0; // delta time
    sf::Clock m_clock;
    std::vector<std::shared_ptr<Updatable>> m_updatables;

    public:
        DrawLayers sprites;
        void draw(sf::RenderTarget&);

        void update();
        void physicsUpdate();
        void addUpdatable(std::shared_ptr<Updatable> updatable);
};
#endif
