#include "MenuScene.hpp"
#include "GameScene.hpp"
#include <TileMap/TileMap.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

bool MenuScene::load() {
    m_play_btn = std::make_shared<GUI::Button>(m_game->getFont(), "Play");
    m_play_btn->setPosition(int(m_game->getViewportSize().x / 2), int(m_game->getViewportSize().y / 2));
    m_play_btn->setTextSize(32);
    sprites.addSprite(m_play_btn, 0);
    addUpdatable(m_play_btn);

    return true;
}

void MenuScene::update(const float& dt) {
    Scene::update(dt);

    if(m_play_btn->isPressed()) {
        m_game->popScene();
        auto game_scene = std::make_shared<GameScene>();

        auto map = std::make_shared<TileMap>();
        if(!map->load("../worlds/world.json"))
            std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
        else
            game_scene->addTileMap(map);

        m_game->addScene(game_scene);
    }

}