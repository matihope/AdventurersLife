#pragma once
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <Updatable/Updatable.hpp>
#include <CollisionShape/CollisionShape.hpp>

class Entity : public sf::Drawable, public sf::Transformable, public Updatable {
    protected:
        CollisionShape m_collision_shape;
        AnimatedSprite m_animation;

    public:
        virtual void update(const float dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
