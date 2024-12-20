cmake_minimum_required(VERSION 3.30)
project(Atlas)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# Find SDL2
find_library(SDL2_LIBRARIES NAMES SDL2)

# Find GLM
find_package(glm REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)

# Include directories
include_directories(${GLM_INCLUDE_DIRS})

add_library(atlas STATIC
        atlas/application/application.cpp
        include/atlas/application.h
        include/atlas/core/core_rendering.h
        include/atlas/graphics.h
        include/atlas/data.hpp
        atlas/core/core_rendering.cpp
        atlas/core/data.cpp
)

add_executable(atlas_test
        atlas_test/main.cpp
        include/atlas/application.h
        include/atlas/core/core_rendering.h
        include/atlas/graphics.h
        include/atlas/data.hpp
)

target_include_directories(atlas PUBLIC ${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

target_link_libraries(atlas PRIVATE glm::glm ${SDL2_LIBRARIES} OpenGL::GL GLEW::GLEW)

target_link_libraries(atlas_test PRIVATE atlas glm::glm)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
