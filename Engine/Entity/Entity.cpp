#include <Entity/Entity.hpp>

void Entity::update(const float& dt) {
    m_animation.update(dt);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_animation, states);
    target.draw(m_collision_shape, states);
}
