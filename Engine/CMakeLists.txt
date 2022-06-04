set(ENGINE_SOURCES
    AnimatedSprite/AnimatedSprite.cpp
    DrawLayers/DrawLayers.cpp
    Entity/Entity.cpp
    Game/Game.cpp
    GUI/Label.cpp
    GUI/Button.cpp
    JsonBridge/JsonBridge.cpp
    Scene/Scene.cpp
    TileMap/TileMap.cpp
    Updatable/Updatable.cpp
    Entity/Entity.cpp
    CollisionShape/CollisionShape.cpp
    Math/Math.cpp
    Tile/Tile.cpp
    ResourceManager/ResourceManager.cpp
)

add_library(Engine ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
