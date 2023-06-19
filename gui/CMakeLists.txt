cmake_minimum_required(VERSION 3.20.5)

set(CXX=g++)
set(SRCS
    src/main.cpp
    src/Renderer.cpp
    src/GameObject.cpp
    src/Socket.cpp
    src/Gui.cpp
    src/Camera.cpp
    src/Light.cpp
    src/Tilemap.cpp
    src/Tile.cpp
    src/ResourceLoader.cpp
    src/Client.cpp
    src/Game.cpp
    src/Player.cpp
    src/Error.cpp
    src/commands/msz.cpp
    src/commands/bct.cpp
    src/commands/pdi.cpp
    src/commands/pin.cpp
    src/commands/plv.cpp
    src/commands/pnw.cpp
    src/commands/ppo.cpp
    src/commands/quit.cpp
    src/commands/tna.cpp
)
set(INCLUDES include)

project(zappy_gui)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zappy_gui ${SRCS})
target_include_directories(zappy_gui PRIVATE ${INCLUDES})
target_link_libraries(zappy_gui OgreBites ${SDL2_LIBRARIES})
