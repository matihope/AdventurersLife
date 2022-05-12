#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <TileMap/TileMap.hpp>
#include <vector>
#include <JsonBridge/JsonBridge.hpp>
#include <iostream>

int main(){

    JsonBridge settings;
    if(!settings.load("settings.json")){
        std::cout << "Could not load settings.json. Make sure settings.json is inside the src folder." << std::endl;
        return 1;
    }

    sf::RenderWindow window(
        sf::VideoMode(
            settings.data["window"]["width"],
            settings.data["window"]["height"]
        ),
        settings.data["window"]["title"]
    );
    window.setVerticalSyncEnabled(settings.data["window"]["vsync"]);

    Game game;
    auto map = std::make_unique<TileMap>();
    map->load("../worlds/world.json");
    game.sprites.addSprite(std::move(map), 0);

    sf::View view(sf::FloatRect(0.f, 0.f, 320.f, 240.f));
    window.setView(view);


    bool run = true;
    while(run){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    run = false;
                    break;
                case sf::Event::Resized:
                    // sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);

                    // window.setView(view);
                    break;
            }
        }
        window.clear(sf::Color(21, 21, 21));


        game.draw(window);
        game.update();
        window.display();
    }
    window.close();
}
