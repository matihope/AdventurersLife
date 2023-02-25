#pragma once
#include <SFML/Graphics.hpp>
#include <GUI/Label.hpp>
#include <Updatable/Updatable.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <memory>

namespace GUI {
    class Button : public WorldEntity {
        Label m_label;
        bool m_is_pressed = false;
        bool m_is_highlighted = false;
        bool m_was_highlighted_previously = false;
        sf::Color m_fill_color = sf::Color::Transparent;
        sf::Color
            m_color_normal = sf::Color(255, 255, 255),
            m_color_hover = sf::Color(200, 200, 200),
            m_color_highlight = sf::Color(125, 125, 125);
        std::unique_ptr<RectCollision> m_collision_shape;
        bool m_has_custom_collision_shape = false;


        public:
            Button();
            Button(sf::Font* font, const std::string text);
            void setFont(sf::Font* font);
            void setText(const std::string newText);
            void setTextSize(unsigned int newSize);
            void update(const float& dt) override;
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            bool isPressed() const;
            void updateDefaultCollisionShape();
            void setCollisionShape(std::unique_ptr<RectCollision> shape);
            const sf::FloatRect getBounds() const;
            void setAlignment(HAlignment newHAlignment, VAlignment newVAlignment);

    };
}
