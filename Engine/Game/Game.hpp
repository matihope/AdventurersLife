#pragma once
#include <SFML/Graphics.hpp>
#include <DrawLayers/DrawLayers.hpp>
#include <Updatable/Updatable.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <memory>
#include <iostream>
#include <stack>

class Scene;

class Game {
    // varibles
    float m_dt = 0; // delta time
    bool m_run = true;
    bool m_enable_print_fps = false;
    float m_physics_update_call_freq;
    float m_physics_update_counter = 0.f;

    // objects
    sf::Clock m_clock;
    JsonBridge m_game_settings;
    sf::RenderWindow m_window;
    std::stack<std::shared_ptr<Scene>> m_scenes_stack;
    sf::View m_view;
    sf::RenderTexture m_draw_target;
    sf::Sprite m_draw_target_sprite;
    sf::Font m_font;

    // funtcions
    const void m_printFPS() const;

    public:
        ~Game();
        bool init(std::string settingsPath);
        void draw();
        void update();
        void pollEvents();
        void setPrintFPS(const bool& printFPS);
        void stop();
        const bool isRunning() const;
        const sf::Vector2u getWindowSize() const;
        const sf::Vector2u getViewportSize() const;
        const sf::RenderWindow& getRenderWindow() const;
        void updateViewportSize();
        void addScene(std::shared_ptr<Scene> newScene);
        void popScene();
        sf::Vector2f getMousePos();
        sf::Font* getFont();
};
