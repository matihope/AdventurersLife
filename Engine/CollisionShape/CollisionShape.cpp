#include <CollisionShape/CollisionShape.hpp>

namespace Debug {
    bool debugDraw = false;
    void setDebugCollisionDraw(bool draw){
        debugDraw = draw;
    }
}

CollisionShape::CollisionShape() {
    m_shape_repr.setOutlineColor(m_outline_color);
    m_shape_repr.setOutlineThickness(1.f);
    m_shape_repr.setFillColor(m_fill_color);
}

void CollisionShape::setShape(const std::vector<sf::Vector2f> points) {
    m_shape = points;
    m_shape_repr.setPointCount(points.size());
    for(size_t i = 0; i < points.size(); ++i)
        m_shape_repr.setPoint(i, points[i]);
}

void CollisionShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!m_draw && !Debug::debugDraw) return;
    states.transform *= getTransform();
    target.draw(m_shape_repr, states);
}

void CollisionShape::setDraw(const bool draw) {
    m_draw = draw;
}
