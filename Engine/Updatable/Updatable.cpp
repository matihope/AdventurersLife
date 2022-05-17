#include <Scene/Scene.hpp>
#include <Updatable/Updatable.hpp>

void Updatable::addScene(Scene* scene){
    m_scene = scene;
}
