cmake_minimum_required(VERSION 3.10)
project(3D_Rendering_Engine)

set(CMAKE_CXX_STANDARD 17)

# Add GLFW (has its own CMake)
add_subdirectory(third_party/glfw)

# Add GLAD manually
add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)

# Include directories for your project
include_directories(
    third_party/glfw/include
    third_party/glad/include
    include
)

# Your executable
add_executable(3D_Rendering_Engine
    src/main.cpp
    third_party/glad/src/glad.c
)

# Link libraries
target_link_libraries(3D_Rendering_Engine PRIVATE glfw glad)
