#include <AnimatedSprite/AnimatedSprite.hpp>
#include <memory>
#include <iostream>

void AnimatedSprite::addAnimation(const Animation& newAnimation, const std::string& name){
    m_animation_names.push_back(name);
    m_animations[name] = std::make_shared<Animation>(newAnimation);
}

std::vector<std::string> const AnimatedSprite::getAnimationNames() const {
    return m_animation_names;
}

void AnimatedSprite::update(const float& dt){
    if(m_animation_names.empty() || (*m_current_animation_ptr).frames.size() == 1)
        return;

    if(!m_is_paused)
        m_frame_time += dt * 1000;

    if(m_frame_time >= (*m_current_animation_ptr).frames[m_current_frame].frameTime){
        m_frame_time -= (*m_current_animation_ptr).frames[m_current_frame].frameTime;
        m_current_frame = (m_current_frame + 1) % (*m_current_animation_ptr).frames.size();
        setTextureRect((*m_current_animation_ptr).frames[m_current_frame].frameRect);
    }
}

void AnimatedSprite::play(const std::string& animationName){
    m_current_frame = 0;
    m_frame_time = 0.f;
    m_current_animation_ptr = m_animations[animationName];
    setTexture((*m_current_animation_ptr).texture);
    setTextureRect((*m_current_animation_ptr).frames[m_current_frame].frameRect);
}

void AnimatedSprite::pause(){
    m_is_paused = true;
}

void AnimatedSprite::resume(){
    m_is_paused = false;
}
