#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>
#include <CollisionComponent/CollisionComponent.hpp>

typedef unsigned long long EntityID;

class WorldEntity : public sf::Drawable, public sf::Transformable, public Updatable {
    private:
        static EntityID id_counter;
        EntityID m_entityId;

        bool m_toKill = false;

    public:
        WorldEntity();
        virtual ~WorldEntity();

        EntityID getId() const;

        void queueFree();
        const bool& isDying() const;
        virtual void _kill();

};
