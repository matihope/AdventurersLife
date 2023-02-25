#pragma once
#include <memory>

class Scene;

class Updatable {
    private:
        Scene* m_scene;

    public:
        void addScene(Scene* scene);
        Scene* getScene();
        virtual void update(const float& dt) {};
        virtual void physicsUpdate(const float dt) {};
        virtual void ready() {};
};
