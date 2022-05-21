#pragma once
#include <SFML/Graphics.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <Updatable/Updatable.hpp>

class Tile : public sf::Drawable, public sf::Transformable, public Updatable {
    bool m_is_animated = false;
    bool m_has_collision = false;
    AnimatedSprite m_sprite;
    CollisionShape m_collision_shape;

    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update(const float& dt);
        void setTexture(const sf::Texture& texture);
        const sf::Texture* getTexture() const;
        void setTextureRect(const sf::IntRect& rectangle);
        const sf::IntRect& getTextureRect() const;
        void setCollisionShape(const CollisionShape& shape);
        void addAnimation(const Animation& animation);
        bool isAnimated() const;
        bool hasCollision() const;
};
