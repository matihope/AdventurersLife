#include <CollisionComponentOld/CollisionComponent.hpp>
#include <Math/Math.hpp>
#include <iostream>

namespace Debug {
    bool debugDraw = false;
    void setDebugCollisionDraw(bool draw) {
        debugDraw = draw;
    }
}

CollisionComponent::CollisionComponent() {
    // m_shape_repr.setOutlineColor(m_outline_color);
    // m_shape_repr.setOutlineThickness(1.f);
    m_shape_repr.setFillColor(m_fill_color);
}

void CollisionComponent::setShape(const std::vector<sf::Vector2f> points) {
    m_shape = points;
    m_shape_repr.setPointCount(points.size());
    for(size_t i = 0; i < points.size(); ++i)
        m_shape_repr.setPoint(i, points[i]);
}

void CollisionComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!m_draw && !Debug::debugDraw) return;
    states.transform *= getTransform();
    target.draw(m_shape_repr, states);
}

void CollisionComponent::setDraw(const bool draw) {
    m_draw = draw;
}

bool CollisionComponent::contains(const sf::Transform& parentTransform, const sf::Vector2f pos) const {
    auto transformedShape = m_shape;
    for(auto& s: transformedShape)
        s = parentTransform.transformPoint(s);
    return Math::isPointInsideConvex(transformedShape, pos);
}

std::vector<sf::Vector2f> CollisionComponent::getShape(sf::Transform parentTransform, const sf::Vector2f& offset) const {
    auto transformedShape = m_shape;
    parentTransform.translate(offset);
    for(auto& s: transformedShape)
        s = parentTransform.transformPoint(s);
    return transformedShape;
}

bool CollisionComponent::intersects(const sf::Transform& parentTransform, const std::vector<sf::Vector2f>& otherShape) const {
    return Math::doShapesIntersect(getShape(parentTransform), otherShape);
}
