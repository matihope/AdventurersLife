#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <DrawLayers/DrawLayers.hpp>

class Game;

// there is no need to inherit from updatable since it's the heighest in the hierarchy
// also updatable has a pointer to a parent scene
class Scene {
    protected:
        Game* m_game;
        std::vector<std::shared_ptr<Updatable>> m_updatables;

    public:
        DrawLayers sprites;
        void addGame(Game* game);
        Game* getGame() const;
        virtual void update(const float& dt);
        virtual void physicsUpdate(const float& dt);
        virtual void draw(sf::RenderTarget& target);
        virtual void addUpdatable(std::shared_ptr<Updatable> updatable);
        virtual void kill() {};
};

#endif
