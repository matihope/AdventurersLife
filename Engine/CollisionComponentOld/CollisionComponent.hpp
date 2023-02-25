#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Debug {
    void setDebugCollisionDraw(bool draw);
}

class CollisionComponent : public sf::Drawable, public sf::Transformable {
    private:
        bool m_draw = false;
        std::vector<sf::Vector2f> m_shape;
        sf::Vector2f center;
        sf::ConvexShape m_shape_repr;
        sf::Color m_outline_color = sf::Color(200.f, 100.f, 125.f, 175.f);
        sf::Color m_fill_color = sf::Color(50.f, 175.f, 255.f, 100.f);

    public:
        CollisionComponent();
        void setShape(std::vector<sf::Vector2f> points);
        std::vector<sf::Vector2f> getShape(sf::Transform parentTransform, const sf::Vector2f& offset = sf::Vector2f(0, 0)) const;
        void setDraw(const bool draw);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool contains(const sf::Transform& parentTransform, const sf::Vector2f pos) const;
        bool intersects(const sf::Transform& parentTransform, const std::vector<sf::Vector2f>& otherShape) const;
        bool rectIntersects(const sf::Transform& parentTransform, const std::vector<sf::Vector2f>& otherShape) const;
};
