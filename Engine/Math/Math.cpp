#include <Math/Math.hpp>
#include <cmath>
#include <iostream>

namespace Math {
    template <class T>
    int sign(T val) {
        if(val > 0)
            return 1;
        if (val < 0)
            return -1;
        return 0;
    }

    sf::Vector2f normalizeVector(const sf::Vector2f vector){
        if(vector.x == 0 || vector.y == 0)
            return vector;
        float length = sqrt(vector.x*vector.x + vector.y*vector.y);
        return {vector.x / length, vector.y / length};
    }

    double determinant(const sf::Vector2f& tail, const::sf::Vector2f& head1, const::sf::Vector2f& head2) {
        return (head1.x - tail.x) * (head2.y - tail.y) - (head2.x - tail.x) * (head1.y - tail.y);
    }

    bool isPointInsideConvex(const std::vector<sf::Vector2f> convex, const sf::Vector2f point) {
        if(convex.size() < 3) return false;

        int intersect_sign = sign(determinant(point, convex.back(), convex.front()));
        bool has_neg = intersect_sign == -1;
        bool has_pos = intersect_sign == 1;
        for(size_t i = 1; i < convex.size(); i++) {
            int now_sign = sign(determinant(point, convex[i - 1], convex[i]));
            if(now_sign == -1) has_neg = true;
            if(now_sign == 1) has_pos = true;
            if(has_neg && has_pos)
                return false;
        }

        return true;
    }
}
