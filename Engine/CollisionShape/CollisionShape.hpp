#pragma once
#include <CollisionComponent/CollisionComponent.hpp>

class CircleCollision : public CollisionComponent {
    private:
        float m_radius;

    public:
        CircleCollision(WorldEntity* parent);
        CircleCollision(WorldEntity* parent, const float& radius);
        ~CircleCollision() {};
        void setRadius(const float& radius);
        const float& getRadius() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool contains(const sf::Vector2f& point) const;

};

class RectCollision : public CollisionComponent {
    private:
        sf::Vector2f m_size;

    public:
        RectCollision(WorldEntity* parent);
        RectCollision(WorldEntity* parent, const float& width, const float& height);
        ~RectCollision() {};
        void setSize(const float& width, const float& height);
        const sf::Vector2f& getSize() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool contains(const sf::Vector2f& point) const;
};
