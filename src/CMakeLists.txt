set(GAME_SOURCES
    Scene/GameScene.cpp Scene/GameScene.hpp
    Scene/MenuScene.cpp Scene/MenuScene.hpp
    Player/Player.cpp Player/Player.hpp
    PlayerLabyrinth/Player.cpp PlayerLabyrinth/Player.hpp
    Scene/LabyrinthScene.cpp Scene/LabyrinthScene.hpp
)

add_library(Game ${GAME_SOURCES})
# target_link_libraries(Game Engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
