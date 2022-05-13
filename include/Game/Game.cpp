#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <iterator>
#include <iostream>

sf::Vector2f scaleToFit(const sf::Vector2f viewSize, const sf::Vector2u windowSize){
    sf::Vector2f scale;
    scale.x = viewSize.x / windowSize.x;
    scale.y = viewSize.y / windowSize.y;
    if(scale.x < scale.y){
        scale.x *= 1 / scale.y;
        scale.y = 1;
    }
    else {
        scale.y *= 1 / scale.x;
        scale.x = 1;
    }
    return scale;
}

Game::~Game(){
    m_window.close();
}

bool Game::init(const std::string settingsPath){
    // initialize variables
    if(!m_game_settings.load("settings.json")){
        std::cout << "Could not load settings.json. Make sure settings.json is inside the src folder." << std::endl;
        return false;
    }

    m_window.create(
        sf::VideoMode(
            m_game_settings.data["window"]["width"],
            m_game_settings.data["window"]["height"]
        ),
        m_game_settings.data["window"]["title"]
    );
    m_window.setVerticalSyncEnabled(m_game_settings.data["window"]["vsync"]);
    m_view.reset(sf::FloatRect(
        0.f,
        0.f,
        m_game_settings.data["viewport"]["width"],
        m_game_settings.data["viewport"]["height"]
        )
    );
    updateViewportSize();

    return true;
}

void Game::draw() {
    m_window.clear(sf::Color(21, 21, 21));

    if(!m_states_stack.empty())
        m_states_stack.top()->draw(m_window);

    m_window.display();
}

void Game::update(){
    m_dt = m_clock.restart().asSeconds();

    if(!m_states_stack.empty())
        m_states_stack.top()->update(m_dt);

    m_printFPS();

}

void Game::addState(std::shared_ptr<State> newState){
    m_states_stack.push(std::move(newState));
}

void Game::pollEvents(){
    sf::Event event;
        while(m_window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    m_run = false;
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            m_run = false;
                            break;
                        case sf::Keyboard::Slash:
                            m_states_stack.pop();
                            break;
                    }
                case sf::Event::Resized:
                    updateViewportSize();
                    break;
            }
        }
}

const bool Game::isRunning() const {
    return m_run;
}

void Game::setPrintFPS(const bool& printFPS){
    m_enable_print_fps = printFPS;
}

const void Game::m_printFPS() const{
    if(m_enable_print_fps)
        printf("%d\n", int(1.f/m_dt));
}

const sf::Vector2u Game::getWindowSize() const {
    return m_window.getSize();
}

void Game::updateViewportSize(){
    sf::Vector2f viewportScale = scaleToFit(m_view.getSize(), getWindowSize());
    m_view.setViewport(sf::FloatRect(sf::Vector2f(0.5f - viewportScale.x / 2, 0.5f - viewportScale.y / 2), viewportScale));
    m_window.setView(m_view);
}
