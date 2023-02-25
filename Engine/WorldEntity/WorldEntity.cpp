#include <WorldEntity/WorldEntity.hpp>

EntityID WorldEntity::id_counter = 0;


WorldEntity::WorldEntity() : m_entityId(id_counter++) {

}

WorldEntity::~WorldEntity() {

}

EntityID WorldEntity::getId() const {
    return m_entityId;
}

const bool& WorldEntity::isDying() const {
    return m_toKill;
}

void WorldEntity::_kill() {

}
