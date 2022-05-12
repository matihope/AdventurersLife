#include <Game/Game.hpp>
#include <iterator>

void Game::draw(sf::RenderTarget& target) {
    target.draw(sprites);
}
