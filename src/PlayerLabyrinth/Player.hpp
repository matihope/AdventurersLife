#pragma once
#include <Updatable/Updatable.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <Entity/Entity.hpp>

class PlayerL : public Entity {
    public:
        void ready();
        void update(const float& dt) override;
        void physicsUpdate(const float dt) override;
};
