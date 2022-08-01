cmake_minimum_required(VERSION 3.23.1)

project(AdventurersLife VERSION 0.1.0)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# SFML
find_package(SFML 2 REQUIRED COMPONENTS window audio graphics system network)
link_libraries(sfml-graphics sfml-window sfml-system)

# LDtkLoader
find_package(LDtkLoader)
set_target_properties(LDtkLoader PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libLDtkLoader.a")
link_libraries(LDtkLoader)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)
endif()

# Link engine
add_subdirectory(Engine)
link_libraries(Engine)
link_directories(Engine)

# Link game's code
add_subdirectory(src)
link_libraries(Game)
link_directories(Game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)
