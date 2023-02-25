#include <GUI/Button.hpp>
#include <Updatable/Updatable.hpp>
#include <Scene/Scene.hpp>
#include <Game/Game.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI {
    Button::Button() {
        m_label.setAlignment(HAlignment::MIDDLE, VAlignment::CENTER);
    }

    Button::Button(sf::Font* font, const std::string text) : Button() {
        setFont(font);
        setText(text);
    }

    void Button::setAlignment(HAlignment newHAlignment, VAlignment newVAlignment){
        m_label.setAlignment(newHAlignment, newVAlignment);
    }


    void Button::setFont(sf::Font* newFont) {
        m_label.setFont(newFont);
        updateDefaultCollisionShape();
    }

    void Button::setText(const std::string newText){
        m_label.setText(newText);
        updateDefaultCollisionShape();
    }

    void Button::setTextSize(unsigned int newSize) {
        m_label.setTextSize(newSize);
        updateDefaultCollisionShape();
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_label, states);

        #if(DEBUG)
            // debugs:
            target.draw(*m_collision_shape, states);
        #endif
    }

    void Button::update(const float& dt) {
        sf::Vector2f mousePos = getScene()->getGame()->getMousePos();
        m_is_highlighted = false;

        if(m_collision_shape->contains(mousePos)){
            m_label.setColor(m_color_hover);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                m_is_highlighted = true;
                m_label.setColor(m_color_highlight);
            }
            else if(m_was_highlighted_previously){
                m_is_pressed = true;
            }
        } else {
            m_label.setColor(m_color_normal);
        }
        m_was_highlighted_previously = m_is_highlighted;
    }

    bool Button::isPressed() const {
        return m_is_pressed;
    }

    // bool Button::isColliding(const sf::Vector2f pos) {
    //     return m_collision_shape.contains(getTransform(), pos);
    // }

    void Button::updateDefaultCollisionShape() {
        if(m_has_custom_collision_shape)
            return;

        sf::FloatRect bounds = getBounds();
        m_collision_shape = std::make_unique<RectCollision>(this, bounds.width, bounds.height);
        m_collision_shape->setPosition(bounds.left, bounds.top);
        m_collision_shape->move(getPosition());
    }

    void Button::setCollisionShape(std::unique_ptr<RectCollision> shape) {
        m_has_custom_collision_shape = true;
        m_collision_shape = std::move(shape);
    }

    const sf::FloatRect Button::getBounds() const {
        // override this when inheriting from Button
        return m_label.getBounds();
    }
}
