#include <Player/Player.hpp>
#include <Math/Math.hpp>
#include <iostream>

void Player::ready() {
    // m_collisionShape.shape.setPointCount(4);
    // m_collisionShape.shape.setPoint(0, sf::Vector2f(0, 0));
    // m_collisionShape.shape.setPoint(1, sf::Vector2f(0, 16));
    // m_collisionShape.shape.setPoint(2, sf::Vector2f(16, 16));
    // m_collisionShape.shape.setPoint(3, sf::Vector2f(16, 0));
    m_collision_shape.setShape({ {-8.f, -8.f}, {-8.f, 8.f}, {8.f, 8.f}, {8.f, -8.f} });
    m_collision_shape.setDraw(true);
}

void Player::update(const float& dt){
    Entity::update(dt);
}

void Player::physicsUpdate(const float dt) {
    int move_x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int move_y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    int rot = sf::Keyboard::isKeyPressed(sf::Keyboard::E) - sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    sf::Vector2f move_vec = sf::Vector2f(move_x, move_y);
    move_vec = Math::normalizeVector(move_vec);
    float spd = 120.f;
    rotate(rot);
    move(move_vec * spd * dt);
    // std::cout << m_animation.getGlobalBounds().left << " " << m_animation.getGlobalBounds().top << std::endl;
    // std::cout << move_vec.x << " " << move_vec.y << std::endl;
}
