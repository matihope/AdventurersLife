#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Math {
    template<class T>
    int sign(T val);
    sf::Vector2f normalizeVector(const sf::Vector2f vector);
    bool isPointInsideConvex(const std::vector<sf::Vector2f> convex, const sf::Vector2f vector);
}
