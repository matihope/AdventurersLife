#ifndef CONTEXT_H
#define CONTEXT_H
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <DrawLayers/DrawLayers.hpp>

class Game;

class Context {
    protected:
        Game* m_game;
        std::vector<std::shared_ptr<Updatable>> m_updatables;

    public:
        DrawLayers sprites;
        void addGame(Game* game);
        virtual void update(const float& dt);
        virtual void draw(sf::RenderTarget& target);
        virtual void addUpdatable(std::shared_ptr<Updatable> updatable);
        virtual void kill() = 0;
};

#endif
