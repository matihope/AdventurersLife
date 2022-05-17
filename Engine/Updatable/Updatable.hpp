#ifndef UPDATABLE_H
#define UPDATABLE_H
#include <memory>

class Scene;

class Updatable {
    protected:
        Scene* m_scene;

    public:
        void addScene(Scene* scene);
        virtual void update(const float& dt) = 0;
        virtual void physicsUpdate(const float& dt) {};
        virtual void ready() {};
};
#endif
