#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <TileMap/TileMap.hpp>
#include <Contexts/GameContext.hpp>
#include <iostream>
#include <memory>
#include <GUI/GUI.hpp>

int main(){

    Game game;
    if(!game.init("settings.json")){
        std::cout << "Could not load settings.json. Make sure settings.json is inside the src folder.\n";
        return 1;
    }

    // game state
    auto map = std::make_shared<TileMap>();
    if(!map->load("../worlds/world.json")){
        std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
        return 1;
    }
    auto game_context = std::make_shared<GameState>();

    auto font = std::make_shared<sf::Font>();
    font->loadFromFile("../resources/HUD/Font/Born2bSportyV2.ttf");
    auto test_label = std::make_shared<GUI::Label>(font);
    test_label->setText("HEsomethin else");
    game_context->sprites.addSprite(test_label, 1);
    test_label->setAlignment(GUI::HAlignment::MIDDLE, GUI::VAlignment::MIDDLE);
    test_label->setTextSize(16);

    game_context->addTileMap(map);
    game.addContext(game_context);


    // menu state

    while(game.isRunning()){
        game.pollEvents();
        game.update();
        sf::Vector2f pos = game.getRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getRenderWindow()));
        test_label->setPosition(int(pos.x), int(pos.y));
        game.draw();
    }
}
