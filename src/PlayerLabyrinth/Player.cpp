#include <PlayerLabyrinth/Player.hpp>
#include <Math/Math.hpp>
#include <Tile/Tile.hpp>
#include <SFML/Graphics.hpp>
#include <Scene/LabyrinthScene.hpp>
#include <Game/Game.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <iostream>

void LoadCharacterAnimations(const std::string& texturePath, AnimatedSprite& animation) {
    Animation walkRight;
    walkRight.texture = texturePath;
    walkRight.frames.push_back({100, sf::IntRect(18, 0, 18, 18)});
    animation.addAnimation(walkRight, "walkRight");

    Animation walkLeft;
    walkLeft.texture = texturePath;
    walkLeft.frames.push_back({100, sf::IntRect(0, 0, 18, 18)});
    animation.addAnimation(walkLeft, "walkLeft");
    // // right
    // Animation idleRight;
    // idleRight.texture = texturePath;
    // idleRight.frames.push_back({100, sf::IntRect(48, 0, 16, 16)});
    // animation.addAnimation(idleRight, "idleRight");
    // animation.play("idleRight");
    // Animation walkRight;
    // walkRight.texture = texturePath;
    // walkRight.frames.push_back({100, sf::IntRect(48, 16, 16, 16)});
    // walkRight.frames.push_back({100, sf::IntRect(48, 32, 16, 16)});
    // walkRight.frames.push_back({100, sf::IntRect(48, 48, 16, 16)});
    // walkRight.frames.push_back({100, sf::IntRect(48, 0, 16, 16)});
    // animation.addAnimation(walkRight, "walkRight");

    // // left
    // Animation idleLeft;
    // idleLeft.texture = texturePath;
    // idleLeft.frames.push_back({100, sf::IntRect(32, 0, 16, 16)});
    // animation.addAnimation(idleLeft, "idleLeft");
    // Animation walkLeft;
    // walkLeft.texture = texturePath;
    // walkLeft.frames.push_back({100, sf::IntRect(32, 16, 16, 16)});
    // walkLeft.frames.push_back({100, sf::IntRect(32, 32, 16, 16)});
    // walkLeft.frames.push_back({100, sf::IntRect(32, 48, 16, 16)});
    // walkLeft.frames.push_back({100, sf::IntRect(32, 0, 16, 16)});
    // animation.addAnimation(walkLeft, "walkLeft");

    // // down
    // Animation idleDown;
    // idleDown.texture = texturePath;
    // idleDown.frames.push_back({100, sf::IntRect(0, 0, 16, 16)});
    // animation.addAnimation(idleDown, "idleDown");
    // Animation walkDown;
    // walkDown.texture = texturePath;
    // walkDown.frames.push_back({100, sf::IntRect(0, 16, 16, 16)});
    // walkDown.frames.push_back({100, sf::IntRect(0, 32, 16, 16)});
    // walkDown.frames.push_back({100, sf::IntRect(0, 48, 16, 16)});
    // walkDown.frames.push_back({100, sf::IntRect(0, 0, 16, 16)});
    // animation.addAnimation(walkDown, "walkDown");

    // // up
    // Animation idleUp;
    // idleUp.texture = texturePath;
    // idleUp.frames.push_back({100, sf::IntRect(16, 0, 16, 16)});
    // animation.addAnimation(idleUp, "idleUp");
    // Animation walkUp;
    // walkUp.texture = texturePath;
    // walkUp.frames.push_back({100, sf::IntRect(16, 16, 16, 16)});
    // walkUp.frames.push_back({100, sf::IntRect(16, 32, 16, 16)});
    // walkUp.frames.push_back({100, sf::IntRect(16, 48, 16, 16)});
    // walkUp.frames.push_back({100, sf::IntRect(16, 0, 16, 16)});
    // animation.addAnimation(walkUp, "walkUp");
}

void PlayerL::ready() {
    m_collision_shape.setShape({ {2.0f, 8.0f}, {14.0f, 8.f}, {14.0f, 14.0f}, {2.0f, 14.0f} });
    // m_collision_shape.setDraw(true);

    LoadCharacterAnimations("../resources/Actor/Characters/Shrek/SpriteSheet.png", m_animation);
    m_shadow.setTexture(ResourceManager::getTexture("../resources/Actor/Characters/Shadow.png"));
    m_shadow.setColor(sf::Color(0, 0, 0, 100));
    m_shadow.setOrigin(m_shadow.getTexture()->getSize().x / 2.0f, m_shadow.getTexture()->getSize().y / 2.0f + 1.5f);
    m_shadow.setScale(1.3f, 1.3f);
    m_shadow.setPosition(sf::Vector2f(9.0f, 18.0f));
}

void PlayerL::update(const float& dt){
    Entity::update(dt);
}

void PlayerL::physicsUpdate(const float dt) {
    int move_x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int move_y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    int rot = sf::Keyboard::isKeyPressed(sf::Keyboard::E) - sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    sf::Vector2f moveVec = sf::Vector2f(move_x, move_y);
    float spd = 60.f;
    moveVec = Math::normalizeVector(moveVec);
    moveVec *= spd * dt;
    rotate(rot);

    LabyrinthScene* scene = (LabyrinthScene*)getScene();
    std::vector<std::shared_ptr<Tile>>& collidableTiles = scene->getTiles();
    for(auto& tile: collidableTiles){
        if(tile->intersects(m_collision_shape.getShape(getTransform(), sf::Vector2f(moveVec.x, 0)))){
            int s = Math::sign(moveVec.x);
            while(moveVec.x * s > 0 && tile->intersects(m_collision_shape.getShape(getTransform(), sf::Vector2f(moveVec.x, 0))))
                moveVec.x -= s * 0.01f;
            if(Math::sign(moveVec.x) != s)
                moveVec.x = 0;
            break;
        }
    }
    for(auto& tile: collidableTiles){
        if(tile->intersects(m_collision_shape.getShape(getTransform(), sf::Vector2f(0, moveVec.y)))){
            int s = Math::sign(moveVec.y);
            while(moveVec.y * s > 0 && tile->intersects(m_collision_shape.getShape(getTransform(), sf::Vector2f(0, moveVec.y))))
                moveVec.y -= s * 0.01f;
            if(Math::sign(moveVec.y) != s)
                moveVec.y = 0;
            break;
        }
    }

    move(moveVec);
    if(moveVec.x != 0){
        if(moveVec.x > 0)
            m_animation.play("walkRight");
        else
            m_animation.play("walkLeft");
    }

    // if(moveVec.x > 0)
    //     m_animation.play("walkRight");
    // else if(moveVec.x < 0)
    //     m_animation.play("walkLeft");
    // else if(moveVec.y > 0)
    //     m_animation.play("walkDown");
    // else if(moveVec.y < 0)
    //     m_animation.play("walkUp");
    // else {
    //     if(m_animation.getCurrentAnimationName().find("Right") != std::string::npos)
    //         m_animation.play("idleRight");
    //     else if (m_animation.getCurrentAnimationName().find("Left") != std::string::npos)
    //         m_animation.play("idleLeft");
    //     else if (m_animation.getCurrentAnimationName().find("Down") != std::string::npos)
    //         m_animation.play("idleDown");
    //     else if (m_animation.getCurrentAnimationName().find("Up") != std::string::npos)
    //         m_animation.play("idleUp");
    // }
    scene->getGame()->setCameraCenter(getPosition());
}
