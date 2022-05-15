#include <Contexts/MenuContext.hpp>
#include <Contexts/GameContext.hpp>
#include <TileMap/TileMap.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

bool MenuContext::load() {
    // std::cout << m_game->getFont()->getInfo().family << std::endl;
    // m_play_btn->setFont(m_game()->getFont());
    // m_play_btn->setText("Play");
    // m_play_btn->setPosition(m_game->getWindowSize().x / 2, m_game->getWindowSize().y / 2);
    // addUpdatable(m_play_btn);

    return true;
}

void MenuContext::update(const float& dt) {
    Context::update(dt);

    // if(m_play_btn->isPressed()) {
    //     m_game->popContext();
    //     auto game_context = std::make_shared<GameContext>();

    //     auto map = std::make_shared<TileMap>();
    //     if(!map->load("../worlds/world.json"))
    //         std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
    //     else
    //         game_context->addTileMap(map);

    //     m_game->addContext(game_context);
    // }

}
