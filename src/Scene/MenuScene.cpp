#include <Scene/MenuScene.hpp>
#include <Scene/GameScene.hpp>
#include <TileMap/TileMap.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

bool MenuScene::load() {
    auto btn = std::make_unique<GUI::Button>(m_game->getFont(), "Play");
    m_play_btn = btn.get();
    m_play_btn->setPosition(int(m_game->getViewportSize().x / 2), int(m_game->getViewportSize().y / 2));

    // #if(DEBUG)
    //     background = std::make_shared<sf::Texture>();
    //     background->loadFromFile("../resources/MusicCover.png");
    //     auto background_spr = std::make_shared<sf::Sprite>();
    //     background_spr->setTexture(*background);
    //     sprites.addSprite(background_spr, 0);
    // #endif

    addEntity(std::move(btn));

    // auto test_btn = std::make_shared<GUI::Button>(m_game->getFont(), "TEST");
    // test_btn->setAlignment(GUI::HAlignment::MIDDLE, GUI::VAlignment::CENTER);
    // test_btn->setPosition(30, int(m_game->getViewportSize().y / 2));
    // test_btn->setTextSize(24);
    // CollisionShape shape;
    // shape.setShape({
    //     {-10, -10},
    //     {20, 0},
    //     {-10, 10}
    // });
    // test_btn->setCollisionShape(shape);
    // sprites.addSprite(test_btn, 0);
    // addUpdatable(test_btn);

    return true;
}

void MenuScene::update(const float& dt) {
    Scene::update(dt);

    if(m_play_btn->isPressed()) {
        auto gameScene = std::make_unique<MenuScene>();
        m_game->replaceTopScene(std::move(gameScene));
    }

}
