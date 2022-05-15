#include <Contexts/Context.hpp>
#include <Updatable/Updatable.hpp>

void Updatable::addContext(Context* context){
    m_context = context;
}
