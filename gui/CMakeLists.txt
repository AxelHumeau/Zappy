cmake_minimum_required(VERSION 3.26.4)

set(SRCS src/main.cpp src/Renderer.cpp src/GameObject.cpp)
set(INCLUDES include)

project(zappy_gui)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(zappy_gui ${SRCS})
target_include_directories(zappy_gui PRIVATE ${INCLUDES})
target_link_libraries(zappy_gui OgreBites)