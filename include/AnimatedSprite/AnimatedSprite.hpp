#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <vector>
#include <map>
#include <memory>

struct Frame {
    uint frameTime;
    sf::IntRect frameRect;
};
typedef std::vector<Frame> Animation;

class AnimatedSprite : public sf::Sprite, public Updatable {

    std::map<std::string, std::shared_ptr<Animation>> m_animations;
    std::string m_current_animation_name;
    std::shared_ptr<Animation> m_current_animation_ptr;
    std::vector<std::string> m_animation_names;
    float m_frame_time = 0.f;
    uint m_current_frame = 0;


    public:
        void update(float dt) override;
        void ready() override {};
        void addAnimation(const Animation newAnimation, std::string animationName);
        void play(const std::string animationName);
        const std::vector<std::string> getAnimationNames() const;
};

#endif
