#include <Tile/Tile.hpp>

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(m_collision_shape, states);
}

void Tile::update(const float& dt){
    if(m_is_animated)
        m_sprite.update(dt);
}

void Tile::addAnimation(const Animation& animation) {
    m_is_animated = true;
    m_sprite.addAnimation(animation, "base");
    m_sprite.play("base");
}

void Tile::setTexture(const sf::Texture& texture) {
    m_sprite.setTexture(texture);
}

const sf::Texture* Tile::getTexture() const {
    return m_sprite.getTexture();
}

void Tile::setTextureRect(const sf::IntRect& rect) {
    m_sprite.setTextureRect(rect);
    Animation animation;
    animation.texture = *m_sprite.getTexture();
    animation.frames.push_back({100, rect});
    m_sprite.addAnimation(animation, "base");
    m_sprite.play("base");
}

const sf::IntRect& Tile::getTextureRect() const {
    return m_sprite.getTextureRect();
}

void Tile::setCollisionShape(const CollisionShape& shape) {
    m_has_collision = true;
    m_collision_shape = shape;
}

const bool Tile::isAnimated() const {
    return m_is_animated;
}

const bool Tile::hasCollision() const {
    return m_has_collision;
}
