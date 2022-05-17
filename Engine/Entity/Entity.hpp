#pragma once
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <Updatable/Updatable.hpp>

class Entity : public AnimatedSprite, public Updatable {
    public:
        Entity();
        
};
