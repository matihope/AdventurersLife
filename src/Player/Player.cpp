#include <Player/Player.hpp>
#include <Math/Math.hpp>
#include <Tile/Tile.hpp>
#include <SFML/Graphics.hpp>
#include <Scene/GameScene.hpp>
#include <Game/Game.hpp>
#include <iostream>

void Player::ready() {
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
    GameScene* scene = (GameScene*)getScene();
    if(m_collision_shape.contains(getTransform(), scene->getGame()->getMousePos() - sf::Vector2f(move_x, 0) * spd * dt))
        move_vec.x = 0;

    if(m_collision_shape.contains(getTransform(), scene->getGame()->getMousePos() - sf::Vector2f(0, move_y) * spd * dt))
        move_vec.y = 0;
    move(move_vec * spd * dt);

    // std::vector<std::shared_ptr<Tile>>& collidableTiles = scene->getTileMap()->getCollidableTiles();
    // for(auto& tile: collidableTiles){
    // }
    // std::cout << m_animation.getGlobalBounds().left << " " << m_animation.getGlobalBounds().top << std::endl;
    // std::cout << move_vec.x << " " << move_vec.y << std::endl;
}
