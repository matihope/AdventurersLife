cmake_minimum_required(VERSION 3.23.1)

project(AdventurersLife VERSION 0.1.0)
enable_testing()
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# SFML
find_package(SFML 2 REQUIRED window audio graphics system network)
link_libraries(sfml-graphics sfml-window sfml-system)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)
endif()
add_subdirectory(Engine)
link_libraries(Engine)
link_directories(Engine)

add_subdirectory(src)
link_libraries(Game)
link_directories(Game)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)
