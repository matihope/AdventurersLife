#pragma once
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <Updatable/Updatable.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <GameObj/GameObj.hpp>

class Entity : public GameObj, public Updatable {
    protected:
        CollisionShape m_collision_shape;
        AnimatedSprite m_animation;
        sf::Sprite m_shadow;

    public:
        virtual void update(const float& dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
