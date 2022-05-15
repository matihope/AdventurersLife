#include <GUI/Label.hpp>

namespace GUI {
    Label::Label(std::shared_ptr<sf::Font> font){
        m_text.setFont(*font);
        m_font = std::move(font);
    }

    void Label::setText(const std::string& newText){
        m_text.setString(newText);
        setAlignment(m_halignment, m_valignment);
    }

    void Label::setAlignment(HAlignment newHAlignment, VAlignment newVAlignment) {
        m_halignment = newHAlignment;
        m_valignment = newVAlignment;
        int textWidth = m_text.getGlobalBounds().width;
        int textHeight = m_text.getGlobalBounds().height;
        sf::Vector2f newPos(-m_text.getLocalBounds().left, -m_text.getLocalBounds().top);
        switch (m_halignment) {
            case HAlignment::MIDDLE:
                newPos.x -= textWidth / 2;
                break;
            case HAlignment::RIGHT:
                newPos.x -= textWidth;
                break;
        }
        switch (m_valignment) {
            case VAlignment::MIDDLE:
                newPos.y -= textHeight / 2;
                break;
            case VAlignment::BOTTOM:
                newPos.y -= textHeight;
                break;
        }
        m_text.setPosition(newPos);
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_text, states);

        // debugs:
        // sf::RectangleShape test;
        // test.setFillColor(sf::Color::Transparent);
        // test.setOutlineThickness(1.f);
        // test.setOutlineColor(sf::Color::Red);
        // test.setSize(sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height));
        // test.setPosition(m_text.getGlobalBounds().left, m_text.getGlobalBounds().top);
        // target.draw(test, states);
    }

    void Label::setTextSize(const uint newSize){
        m_text.setCharacterSize(newSize);
        setAlignment(m_halignment, m_valignment);
    }

}
