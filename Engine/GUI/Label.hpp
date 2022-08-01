#pragma once
#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <memory>
namespace GUI {
    enum class HAlignment {
        LEFT,
        MIDDLE,
        RIGHT
    };

    enum class VAlignment {
        TOP,
        CENTER,
        BOTTOM
    };

    class Label : public WorldEntity {
        sf::Font* m_font;
        HAlignment m_halignment = HAlignment::LEFT;
        VAlignment m_valignment = VAlignment::TOP;
        sf::Text m_text;

        public:
            Label();
            Label(sf::Font* font);
            void setFont(sf::Font* font);
            void setText(const std::string& text);
            void setAlignment(HAlignment newHAlignment, VAlignment newVAlignment);
            void setTextSize(const unsigned int newSize);
            void setColor(const sf::Color newColor);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            const sf::FloatRect getBounds() const;
    };
}
