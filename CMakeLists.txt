cmake_minimum_required(VERSION 3.10)
project(3D_Rendering_Engine)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(third_party/glfw)


add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)


include_directories(
    third_party/glfw/include
    third_party/glad/include
    third_party/glm
    include/third_party
    
    include
)


add_executable(3D_Rendering_Engine
    src/main.cpp
    third_party/glad/src/glad.c
)


target_link_libraries(3D_Rendering_Engine PRIVATE glfw glad)
