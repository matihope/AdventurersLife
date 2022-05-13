#ifndef UPDATABLE_H
#define UPDATABLE_H
#include <memory>

class Updatable {
    public:
        virtual void update(const float& dt) = 0;
        virtual void ready() = 0;
};
#endif
