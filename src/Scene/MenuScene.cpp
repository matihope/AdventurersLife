#include <Scene/MenuScene.hpp>
#include <Scene/GameScene.hpp>
#include <TileMap/TileMap.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

bool MenuScene::load() {
    m_play_btn = std::make_shared<GUI::Button>(m_game->getFont(), "Play");
    m_play_btn->setPosition(int(m_game->getViewportSize().x / 2), int(m_game->getViewportSize().y / 2));

    #if(DEBUG)
        background = std::make_shared<sf::Texture>();
        background->loadFromFile("../resources/MusicCover.png");
        auto background_spr = std::make_shared<sf::Sprite>();
        background_spr->setTexture(*background);
        sprites.addSprite(background_spr, 0);
    #endif

    sprites.addSprite(m_play_btn, 0);
    addUpdatable(m_play_btn);

    auto test_btn = std::make_shared<GUI::Button>(m_game->getFont(), "TEST");
    test_btn->setAlignment(GUI::HAlignment::MIDDLE, GUI::VAlignment::CENTER);
    test_btn->setPosition(30, int(m_game->getViewportSize().y / 2));
    test_btn->setTextSize(24);
    CollisionShape shape;
    shape.setShape({
        {-10, -10},
        {20, 0},
        {-10, 10}
    });
    test_btn->setCollisionShape(shape);
    sprites.addSprite(test_btn, 0);
    addUpdatable(test_btn);

    return true;
}

void MenuScene::update(const float& dt) {
    Scene::update(dt);

    if(m_play_btn->isPressed()) {
        m_game->popScene();
        auto game_scene = std::make_shared<GameScene>();
        m_game->addScene(game_scene);
        game_scene->load();
    }

}
