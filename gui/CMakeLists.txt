cmake_minimum_required(VERSION 3.20.5)

set(SRCS src/main.cpp src/Renderer.cpp src/GameObject.cpp src/Camera.cpp src/Light.cpp src/ResourceLoader.cpp)
set(INCLUDES include)

project(zappy_gui)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zappy_gui ${SRCS})
target_include_directories(zappy_gui PRIVATE ${INCLUDES})
target_link_libraries(zappy_gui OgreBites ${SDL2_LIBRARIES})
