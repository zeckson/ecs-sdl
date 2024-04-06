cmake_minimum_required(VERSION 3.27.8)

project(ECS)

# Set up C/C++ compilers
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# Create an imported target for SDL2
add_library(SDL2 INTERFACE IMPORTED)

# Create a variable to hold the list of source files
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB MAIN "src/*.cpp")

# Add an executable target named "myExecutable" from the globbed source files
add_executable(ECSSDL2 ${MAIN} ${SOURCES})

# Include SDL2 directories
target_include_directories(ECSSDL2 PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(ECSSDL2 PRIVATE ${SDL2_ttf_INCLUDE_DIRS})
target_include_directories(ECSSDL2 PRIVATE ${SDL2_image_INCLUDE_DIRS})
target_compile_options(ECSSDL2 PRIVATE -mmacosx-version-min=14.0)


# Link SDL2 libraries
target_link_libraries(ECSSDL2 PRIVATE SDL2::SDL2)
target_link_libraries(ECSSDL2 PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(ECSSDL2 PRIVATE SDL2_image::SDL2_image)
