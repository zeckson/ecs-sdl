cmake_minimum_required(VERSION 3.27.8)

project(ECS)

# Set up C/C++ compilers
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

if (APPLE)
    add_compile_options(-mmacosx-version-min=14.0)
    # Add macOS-specific configuration here
endif ()

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# Add ECS Engine library
add_subdirectory(engine)

# Add an executable target named "SpaceShips"
add_executable(SpaceShips
        spaceships/src/spaceshipgame.cpp
        spaceships/src/main.cpp
)
target_link_libraries(SpaceShips PRIVATE ZECSEngine)

# Add an executable target named "GameOfBalls"
add_executable(GameOfBalls
        gameofballs/src/ballgame.cpp
        gameofballs/src/entityconfig.cpp
        gameofballs/src/main.cpp
)
target_link_libraries(GameOfBalls PRIVATE ZECSEngine)

