#include <GUI/Label.hpp>

namespace GUI {
    Label::Label(sf::Font* font) {
        setFont(font);
    }

    void Label::setFont(sf::Font* font){
        m_text.setFont(*font);
        m_font = font;
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
            case VAlignment::CENTER:
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
    }

    void Label::setTextSize(const uint newSize){
        #if (SFML_VERSION_MINOR <= 5)
            // weird hack to turn off font smoothing...
            sf::Texture& texture = const_cast<sf::Texture&>(m_font->getTexture(newSize));
            texture.setSmooth(false);
        #else
            m_font->setSmooth(false);
        #endif
        m_text.setCharacterSize(newSize);
        setAlignment(m_halignment, m_valignment);
    }

    void Label::setColor(const sf::Color newColor) {
        m_text.setFillColor(newColor);
    }

    const sf::FloatRect Label::getBounds() const {
        return m_text.getGlobalBounds();
    }

}
