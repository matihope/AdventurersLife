#pragma once
#include <SFML/Graphics.hpp>
#include <GUI/Label.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>

namespace GUI {
    class Button : public sf::Drawable, public sf::Transformable, public Updatable {
        Label m_label;
        bool m_is_pressed = false;
        bool m_is_highlighted = false;
        bool m_was_highlighted_previously = false;
        sf::Color m_fill_color = sf::Color::Transparent;
        sf::Color
            m_color_normal = sf::Color(255, 255, 255),
            m_color_hover = sf::Color(200, 200, 200),
            m_color_highlight = sf::Color(125, 125, 125);
        sf::FloatRect m_bounds;

        public:
            Button();
            Button(sf::Font* font, const std::string text);
            void setFont(sf::Font* font);
            void setText(const std::string newText);
            void setTextSize(unsigned int newSize);
            virtual void update(const float& dt) override;
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            bool isPressed() const;
    };
}
