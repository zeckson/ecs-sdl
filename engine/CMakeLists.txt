cmake_minimum_required(VERSION 3.28)

project(ECSEngine)

# Set up C/C++ compilers
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
file(GLOB_RECURSE ENGINE_HEADERS "src/*.h")
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
add_library(ZECSEngine STATIC
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES})
target_include_directories(ZECSEngine PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src)

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
