#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <GUI/Label.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>

namespace GUI {
    class Button : public sf::Drawable, public sf::Transformable, public Updatable {
        Label m_label;
        bool m_is_pressed = false;

        public:
            Button();
            Button(sf::Font* font, const std::string text);
            void setFont(sf::Font* font);
            void setText(const std::string newText);
            void setTextSize(uint newSize);
            virtual void update(const float& dt) override;
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            const bool isPressed() const;
    };
}


#endif
