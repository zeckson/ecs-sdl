cmake_minimum_required(VERSION 3.27.8)

project(ECS)

# Set up C/C++ compilers
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags

# Find SDL2 package
#include(FindPkgConfig)
find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_ttf REQUIRED SDL2_ttf)
find_package(SDL2_image REQUIRED SDL2_image)

# Create a variable to hold the list of source files
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB MAIN "src/*.cpp")

# Add an executable target named "myExecutable" from the globbed source files
add_executable(ECSSDL2 ${MAIN} ${SOURCES})

get_cmake_property(VARIABLES_LIST VARIABLES)
message("List of CMake variables:")
foreach(VARIABLE ${VARIABLES_LIST})
    message("  ${VARIABLE} = ${${VARIABLE}}")
endforeach()

# Include SDL2 directories
message("SDL2: ${SDL2}")
target_include_directories(ECSSDL2 PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(ECSSDL2 PRIVATE ${SDL2_ttf_INCLUDE_DIRS})
target_include_directories(ECSSDL2 PRIVATE ${SDL2_image_INCLUDE_DIRS})
target_compile_options(ECSSDL2 PRIVATE -Wall -O0 -mmacosx-version-min=14.0)
target_compile_options(ECSSDL2 PRIVATE ${SDL2_CFLAGS_OTHER})
target_compile_options(ECSSDL2 PRIVATE ${SDL2_LDFLAGS})


# Link SDL2 libraries
message("Value of SDL Libraries: ${SDL2_LIBRARIES}")
target_link_libraries(ECSSDL2 PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(ECSSDL2 PRIVATE ${SDL2_ttf_LIBRARIES})
target_link_libraries(ECSSDL2 PRIVATE SDL2_image::SDL2_image)
message("Value of SDL Libraries inside: ${${SDL2_LIBRARIES}}")
target_link_options(ECSSDL2 PRIVATE ${SDL2_LDFLAGS})
