#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <Contexts/MenuContext.hpp>
#include <memory>

int main(){

    Game game;
    if(!game.init("settings.json"))
        return 1;

    auto menuContext = std::make_shared<MenuContext>();
    menuContext->load();
    game.addContext(menuContext);

    while(game.isRunning()){
        game.pollEvents();
        game.update();
        game.draw();
    }
}
