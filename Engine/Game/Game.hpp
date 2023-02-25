#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <GUI/Label.hpp>
#include <memory>
#include <iostream>
#include <stack>

class Scene;

class Game {
    // varibles
    bool m_run = true;
    float m_dt = 0; // delta time
    double m_fps_sum = 0.0;
    unsigned int m_fps_frame_count = 0;
    bool m_enable_print_fps = false;
    float m_physics_update_call_freq;
    float m_physics_update_counter = 0.f;

    // objects
    sf::Clock m_clock;
    JsonBridge m_game_settings;
    sf::RenderWindow m_window;
    std::stack<std::unique_ptr<Scene>> m_scenes_stack;
    sf::View m_view;
    sf::Font m_font;
    GUI::Label m_fps_label;

    public:
        ~Game();
        bool init(std::string settingsPath);
        void draw();
        void update();
        void pollEvents();
        void setPrintFPS(const bool& printFPS);
        void stop();
        bool isRunning() const;
        const sf::Vector2u getWindowSize() const;
        const sf::Vector2u getViewportSize() const;
        const sf::RenderWindow& getRenderWindow() const;
        void updateViewportSize();
        bool addScene(std::unique_ptr<Scene> newScene);
        bool replaceTopScene(std::unique_ptr<Scene> newScene);
        void popScene();
        sf::Vector2f getMousePos();
        sf::Font* getFont();
        sf::View* getView();
        bool isRectInsideView(const sf::FloatRect& rect);
        void setCameraCenter(const sf::Vector2f& pos);
};
