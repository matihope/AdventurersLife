#ifndef UPDATABLE_H
#define UPDATABLE_H
class Updatable {
    public:
        virtual void update(float dt) = 0;
        virtual void ready() = 0;
};
#endif
