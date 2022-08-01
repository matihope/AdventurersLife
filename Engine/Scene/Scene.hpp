#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <list>

class Game;

// there is no need to inherit from updatable since it's the heighest in the hierarchy
// also updatable has a pointer to a parent scene
class Scene {
    protected:
        Game* m_game;
        std::map<unsigned int, std::list<std::unique_ptr<WorldEntity>>> m_entity_pool;

    public:
        void addGame(Game* game);
        Game* getGame() const;
        virtual bool load() = 0;
        virtual void cleanEntities();
        virtual void update(const float& dt);
        virtual void physicsUpdate(const float& dt);
        virtual void draw(sf::RenderTarget& target);
        virtual void addEntity(std::unique_ptr<WorldEntity> entity, unsigned int drawOrder = 0);
        virtual void kill() {};
        virtual void handleEvent(const sf::Event& event) {};
};
