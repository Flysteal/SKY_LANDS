cmake_minimum_required(VERSION 3.28.3)
project(SKY_LANDS VERSION 0.1.0 LANGUAGES C CXX)
include(FindPkgConfig)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH GLFW_DIR "${CMAKE_SOURCE_DIR}/include/glfw")

# Find GLFW
find_package(glfw3 REQUIRED PATHS ${GLFW_DIR})

find_package(OpenGL REQUIRED)

# Find the gtkmm library
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)


# Include the gtkmm headers
include_directories(${GTKMM_INCLUDE_DIRS})
# Include directoriess
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/HeaderFiles)
include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/backends)

# Find all .cpp files in src directory 
file(GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/backends/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable target

link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(SKY_LANDS ${SOURCES} src/glad.c)

# Link OpenGL and GLFW to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES})
target_link_libraries(SKY_LANDS PRIVATE glfw)