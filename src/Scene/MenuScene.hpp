#pragma once
#include <Scene/Scene.hpp>
#include <GUI/GUI.hpp>

class MenuScene : public Scene {
    GUI::Button* m_play_btn;
    std::unique_ptr<sf::Texture> background;

    public:
        bool load();
        void update(const float& dt) override;
};
