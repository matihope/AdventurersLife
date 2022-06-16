#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <memory>
#include <Scene/MenuScene.hpp>

int main(){

    Game game;
    if(!game.init("settings.json"))
        return 1;

    auto menuScene = std::make_unique<MenuScene>();
    game.addScene(std::move(menuScene));

    while(game.isRunning()){
        game.pollEvents();
        game.update();
        game.draw();
    }
}
