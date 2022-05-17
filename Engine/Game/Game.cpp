#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <Game/Game.hpp>
#include <iterator>
#include <iostream>

sf::Vector2f scaleToFit(const sf::Vector2f viewSize, const sf::Vector2u windowSize) {
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

Game::~Game() {
    m_window.close();
}

bool Game::init(const std::string settingsPath) {
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

    // an intermediate draw target
    m_draw_target.create(
        m_game_settings.data["window"]["width"],
        m_game_settings.data["window"]["height"]
    );
    m_draw_target.setSmooth(false);
    m_draw_target_sprite.setScale(
        float(m_game_settings.data["window"]["width"]) / int(m_game_settings.data["viewport"]["width"]),
        float(m_game_settings.data["window"]["height"]) / int(m_game_settings.data["viewport"]["height"])
    );

    m_view.reset(sf::FloatRect(
        0.f,
        0.f,
        m_game_settings.data["window"]["width"],
        m_game_settings.data["window"]["height"]
        )
    );
    updateViewportSize();

    setPrintFPS(m_game_settings.data["debug"]["printFPS"]);
    m_physics_update_call_freq = 1.f / int(m_game_settings.data["engine"]["physicsUpdateCallFreq"]);
    if(!m_font.loadFromFile(m_game_settings.data["engine"]["fontPath"])){
        std::cout << "Failed to load font" << std::endl;
    }


    return true;
}

void Game::draw() {
    m_window.clear(sf::Color(21, 21, 21));
    m_draw_target.clear(sf::Color(21, 21, 21));

    if(!m_scenes_stack.empty())
        m_scenes_stack.top()->draw(m_draw_target);

    m_draw_target.display();
    m_draw_target_sprite.setTexture(m_draw_target.getTexture());
    m_window.draw(m_draw_target_sprite);
    m_window.display();
}

void Game::update() {
    m_dt = m_clock.restart().asSeconds();


    if(!m_scenes_stack.empty())
        m_scenes_stack.top()->update(m_dt);

    m_physics_update_counter += m_dt;
    if(m_physics_update_counter >= m_physics_update_call_freq){
        if(!m_scenes_stack.empty())
            m_scenes_stack.top()->physicsUpdate(m_physics_update_call_freq);
        m_physics_update_counter -= m_physics_update_call_freq;
    }

    m_printFPS();

}

void Game::addScene(std::shared_ptr<Scene> newState) {
    newState->addGame(this);
    m_scenes_stack.push(std::move(newState));
}

void Game::popScene() {
    m_scenes_stack.top()->kill();
    m_scenes_stack.pop();
}

void Game::pollEvents() {
    sf::Event event;
        while(m_window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    stop();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            stop();
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

void Game::stop() {
    m_run = false;
}

void Game::setPrintFPS(const bool& printFPS) {
    m_enable_print_fps = printFPS;
}

const void Game::m_printFPS() const {
    if(m_enable_print_fps)
        printf("%d\n", int(1.f/m_dt));
}

const sf::Vector2u Game::getWindowSize() const {
    return m_window.getSize();
}

const sf::Vector2u Game::getViewportSize() const {
    return { m_game_settings.data["viewport"]["width"], m_game_settings.data["viewport"]["height"] };
}

const sf::RenderWindow& Game::getRenderWindow() const {
    return m_window;
}

void Game::updateViewportSize() {
    sf::Vector2f viewportScale = scaleToFit(m_view.getSize(), getWindowSize());
    m_view.setViewport(sf::FloatRect(sf::Vector2f(0.5f - viewportScale.x / 2, 0.5f - viewportScale.y / 2), viewportScale));
    m_window.setView(m_view);
}

sf::Vector2f Game::getMousePos() {
    sf::Vector2f pos = getRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(getRenderWindow()));
    pos.x /= m_draw_target_sprite.getScale().x;
    pos.y /= m_draw_target_sprite.getScale().y;
    return pos;
}

sf::Font* Game::getFont() {
    return &m_font;
}
