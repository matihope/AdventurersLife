#ifndef UPDATABLE_H
#define UPDATABLE_H
#include <memory>

class Context;

class Updatable {
    protected:
        Context* m_context;

    public:
        void addContext(Context* context);
        virtual void update(const float& dt) = 0;
        virtual void physicsUpdate(const float& dt) {};
        virtual void ready() {};
};
#endif
