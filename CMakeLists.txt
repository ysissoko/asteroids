cmake_minimum_required(VERSION 3.10)
project(Asteroids VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (debug or release)" FORCE)
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(config.h.in config.h)

# find sfml library installed on filesystem
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

# libs
list(APPEND EXTRA_LIBS sfml-graphics sfml-audio)
list(APPEND EXTRA_LIBS spdlog::spdlog)
list(APPEND EXTRA_LIBS nlohmann_json::nlohmann_json)

# Sources
list(APPEND SOURCES src/main.cpp)

## Controllers
list(APPEND SOURCES src/controllers/controller.cpp)
list(APPEND SOURCES src/controllers/pc-controller.cpp)

### Actions
list(APPEND SOURCES src/controllers/actions/vehicle/accelerate.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/deccelerate.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/rotate-ccw.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/rotate-cw.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/shoot.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/stop-rotate.cpp)
list(APPEND SOURCES src/controllers/actions/vehicle/stop-shoot.cpp)

list(APPEND SOURCES src/fsm/vehicle/states/vehicle-state.cpp)
list(APPEND SOURCES src/vehicle/bullet.cpp)
list(APPEND SOURCES src/renderer/soundplayer.cpp)

## Asteroids
list(APPEND SOURCES src/asteroids/asteroid.cpp)
list(APPEND SOURCES src/asteroids/generator.cpp)

## Game
list(APPEND SOURCES src/game/game.cpp)
list(APPEND SOURCES src/game/game-object.cpp)
list(APPEND SOURCES src/game/game-state.cpp)

## Renderer
list(APPEND SOURCES src/renderer/renderer.cpp)

## Simulator
list(APPEND SOURCES src/simulator/simulator.cpp)

## Vehicle
list(APPEND SOURCES src/vehicle/vehicle.cpp)

add_executable(Asteroids ${SOURCES})

target_link_libraries(Asteroids PRIVATE ${EXTRA_LIBS})

target_include_directories(Asteroids 
                            PUBLIC "${PROJECT_BINARY_DIR}"
                            PRIVATE "${PROJECT_SOURCE_DIR}")
