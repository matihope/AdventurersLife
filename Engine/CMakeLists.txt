set(ENGINE_SOURCES
    AnimatedSprite/AnimatedSprite.cpp AnimatedSprite/AnimatedSprite.hpp
    DrawLayers/DrawLayers.cpp DrawLayers/DrawLayers.hpp
    Entity/Entity.cpp Entity/Entity.hpp
    Game/Game.cpp Game/Game.hpp
    GUI/Label.cpp GUI/Label.hpp
    GUI/Button.cpp GUI/Button.hpp
    JsonBridge/JsonBridge.cpp JsonBridge/JsonBridge.hpp
    Scene/Scene.cpp Scene/Scene.hpp
    TileMap/TileMap.cpp TileMap/TileMap.hpp
    Updatable/Updatable.cpp Updatable/Updatable.hpp
    Entity/Entity.cpp Entity/Entity.hpp
    CollisionShape/CollisionShape.cpp CollisionShape/CollisionShape.hpp
    Math/Math.cpp Math/Math.hpp
    Tile/Tile.cpp Tile/Tile.hpp
)

add_library(Engine ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
