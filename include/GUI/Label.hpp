#ifndef LABEL_H
#define LABEL_H
#include <SFML/Graphics.hpp>
#include <memory>


namespace GUI {
    enum class HAlignment {
        LEFT,
        MIDDLE,
        RIGHT
    };

    enum class VAlignment {
        TOP,
        MIDDLE,
        BOTTOM
    };

    class Label : public sf::Drawable, public sf::Transformable {
        std::shared_ptr<sf::Font> m_font;
        HAlignment m_halignment = HAlignment::LEFT;
        VAlignment m_valignment = VAlignment::TOP;
        sf::Text m_text;

        public:
            Label(std::shared_ptr<sf::Font> font);
            void setText(const std::string& text);
            void setAlignment(HAlignment newHAlignment, VAlignment newVAlignment);
            void setTextSize(const uint newSize);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}


#endif
