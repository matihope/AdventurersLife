#pragma once
#include <Scene/Scene.hpp>
#include <GUI/GUI.hpp>

class MenuScene : public Scene {
    std::shared_ptr<GUI::Button> m_play_btn;
    std::shared_ptr<sf::Texture> background;

    public:
        bool load();
        void update(const float& dt) override;
};
