#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <Updatable/Updatable.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <States/State.hpp>
#include <memory>
#include <iostream>
#include <stack>

class Game {
    // varibles
    float m_dt = 0; // delta time
    bool m_run = true;
    bool m_enable_print_fps = false;

    // objects
    sf::Clock m_clock;
    JsonBridge m_game_settings;
    sf::RenderWindow m_window;
    std::stack<std::shared_ptr<State>> m_states_stack;
    sf::View m_view;

    // funtcions
    const void m_printFPS() const;

    public:
        ~Game();
        bool init(std::string settingsPath);
        void draw();
        void update();
        void physicsUpdate();
        void pollEvents();
        void setPrintFPS(const bool& printFPS);
        const bool isRunning() const;
        const sf::Vector2u getWindowSize() const;
        void updateViewportSize();
        void addState(std::shared_ptr<State> newState);
};
#endif
