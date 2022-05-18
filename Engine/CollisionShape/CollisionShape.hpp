#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Debug {
    void setDebugCollisionDraw(bool draw);
}

class CollisionShape : public sf::Drawable, public sf::Transformable {
    bool m_draw = false;
    std::vector<sf::Vector2f> m_shape;
    sf::ConvexShape m_shape_repr;
    sf::Color m_outline_color = sf::Color(200.f, 100.f, 125.f, 175.f);
    sf::Color m_fill_color = sf::Color(50.f, 175.f, 255.f, 100.f);

    public:
        CollisionShape();
        void setShape(std::vector<sf::Vector2f> points);
        void setDraw(const bool draw);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
