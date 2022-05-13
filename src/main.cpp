#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <TileMap/TileMap.hpp>
#include <States/GameState.hpp>
#include <iostream>
#include <memory>

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
    auto game_state = std::make_shared<GameState>();
    game_state->addTileMap(map);
    game.addState(game_state);

    // menu state

    while(game.isRunning()){
        game.pollEvents();
        game.draw();
        game.update();
    }
}
