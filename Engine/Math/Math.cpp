#include <Math/Math.hpp>
#include <cmath>

namespace Math {
    sf::Vector2f normalizeVector(const sf::Vector2f vector){
        if(vector.x == 0 || vector.y == 0)
            return vector;
        float length = sqrt(vector.x*vector.x + vector.y*vector.y);
        return {vector.x / length, vector.y / length};
    }
}
