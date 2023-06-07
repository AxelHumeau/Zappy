cmake_minimum_required(VERSION 3.20.5)

set(CXX=g++)
set(SRCS src/main.cpp src/Renderer.cpp src/GameObject.cpp src/Socket.cpp src/Camera.cpp src/Light.cpp src/Tilemap.cpp src/Tile.cpp src/Error.cpp)
set(INCLUDES include)

project(zappy_gui)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(zappy_gui ${SRCS})
target_include_directories(zappy_gui PRIVATE ${INCLUDES})
target_link_libraries(zappy_gui OgreBites)
