cmake_minimum_required(VERSION 3.20.5)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COMPILE_FLAGS}")

set(CXX=g++)
set(SRCS
    src/main.cpp
    src/Renderer.cpp
    src/GameObject.cpp
    src/Socket.cpp
    src/Gui.cpp
    src/MainMenu.cpp
    src/Panel.cpp
    src/Button.cpp
    src/Camera.cpp
    src/Light.cpp
    src/Tilemap.cpp
    src/Tile.cpp
    src/ResourceLoader.cpp
    src/Client.cpp
    src/Game.cpp
    src/Player.cpp
    src/Utils.cpp
    src/Error.cpp
    src/Particles/Particle.cpp
    src/Particles/BroadcastParticle.cpp
    src/commands/msz.cpp
    src/commands/bct.cpp
    src/commands/pdi.cpp
    src/commands/pin.cpp
    src/commands/plv.cpp
    src/commands/pnw.cpp
    src/commands/ppo.cpp
    src/commands/quit.cpp
    src/commands/tna.cpp
    src/commands/pex.cpp
    src/commands/pbc.cpp
    src/commands/pic.cpp
    src/commands/pie.cpp
    src/commands/pfk.cpp
    src/commands/pdr.cpp
    src/commands/pgt.cpp
    src/commands/enw.cpp
    src/commands/ebo.cpp
    src/commands/edi.cpp
    src/commands/sgt.cpp
    src/commands/sst.cpp
    src/commands/seg.cpp
    src/commands/smg.cpp
    src/commands/suc.cpp
    src/commands/sbp.cpp
)
set(INCLUDES include)

project(zappy_gui)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zappy_gui ${SRCS})
target_include_directories(zappy_gui PRIVATE ${INCLUDES})
target_link_libraries(zappy_gui OgreBites ${SDL2_LIBRARIES})
