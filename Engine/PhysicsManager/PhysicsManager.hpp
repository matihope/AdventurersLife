#pragma once
#include <list>
#include <CollisionShape/CollisionShape.hpp>

class PhysicsManager {
    private:
        std::list<RectCollision*> m_rect_collision_list;
        std::list<CircleCollision*> m_circle_collision_list;

    public:
        void addRectCollision(RectCollision* rect);
        void addCircleCollision(CircleCollision* circle);
        sf::Vector2f moveAndSlide(RectCollision* collider, sf::Vector2f veclocity);
};
