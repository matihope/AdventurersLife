#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <vector>
#include <map>
#include <memory>

struct Frame {
    uint frameTime;
    sf::IntRect frameRect;
};

struct Animation {
    std::shared_ptr<sf::Texture> texture;
    std::vector<Frame> frames;
};

class AnimatedSprite : public sf::Sprite, public Updatable {
    // variables
    float m_frame_time = 0.f;
    uint m_current_frame = 0;
    bool m_is_paused = false;

    // objects
    std::map<std::string, std::shared_ptr<Animation>> m_animations;
    std::string m_current_animation_name;
    std::shared_ptr<Animation> m_current_animation_ptr;
    std::vector<std::string> m_animation_names;


    public:
        void update(const float& dt) override;
        void addAnimation(const Animation& newAnimation, const std::string& animationName);
        void play(const std::string& animationName);
        void pause();
        void resume();
        const std::vector<std::string> getAnimationNames() const;
};
