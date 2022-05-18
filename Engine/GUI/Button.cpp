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

    void Button::setFont(sf::Font* newFont) {
        m_label.setFont(newFont);
    }

    void Button::setText(const std::string newText){
        m_label.setText(newText);
    }

    void Button::setTextSize(uint newSize) {
        m_label.setTextSize(newSize);
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        // debugs:
        // sf::RectangleShape test;
        // test.setPosition(-10.f, -10.f);
        // test.setSize(sf::Vector2f(20.f, 20.f));
        // test.setFillColor(sf::Color::Transparent);
        // test.setOutlineColor(sf::Color::Green);
        // test.setOutlineThickness(1.f);
        // target.draw(test, states);

        target.draw(m_label, states);
    }

    void Button::update(const float dt) {
        sf::Vector2f mousePos = m_scene->getGame()->getMousePos();
        m_bounds = m_label.getBounds();
        m_bounds.top += getPosition().y;
        m_bounds.left += getPosition().x;
        m_is_highlighted = false;
        if(m_bounds.contains(mousePos)){
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

    const bool Button::isPressed() const {
        return m_is_pressed;
    }
}
