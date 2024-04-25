cmake_minimum_required(VERSION 3.27.8)

project(ECS)

# Set up C/C++ compilers
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
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
file(GLOB_RECURSE ENGINE_HEADERS "engine/*.h")
file(GLOB_RECURSE ENGINE_SOURCES "engine/*.cpp")
add_library(ZECSEngine STATIC
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES})
target_include_directories(ZECSEngine PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/engine)

target_sources(ZECSEngine PUBLIC ${ENGINE_HEADERS})
target_sources(ZECSEngine PRIVATE ${ENGINE_SOURCES})

# Include SDL2 directories
target_include_directories(ZECSEngine PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(ZECSEngine PRIVATE ${SDL2_ttf_INCLUDE_DIRS})
target_include_directories(ZECSEngine PRIVATE ${SDL2_image_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(ZECSEngine PUBLIC SDL2::SDL2)
target_link_libraries(ZECSEngine PUBLIC SDL2_ttf::SDL2_ttf)
target_link_libraries(ZECSEngine PUBLIC SDL2_image::SDL2_image)

# Create a variable to hold the list of source files
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB MAIN "src/*.cpp")

# Add an executable target named "myExecutable" from the globbed source files
add_executable(ECSSDL2 ${MAIN} ${SOURCES})

target_link_libraries(ECSSDL2 PRIVATE ZECSEngine)
