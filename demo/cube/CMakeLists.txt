
cmake_minimum_required(VERSION 4.1)

find_package(OpenCASCADE REQUIRED)
add_subdirectory(../../third_party/glfw glfw_build)

add_library(glad STATIC ../../third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC ../../third_party/glad/include ${OpenCASCADE_INCLUDE_DIR})

add_executable(cube_demo
    cube.cpp
    ../../src/Shader.cpp
    ../../src/Camera.cpp
    ../../src/Renderer.cpp
    ../../src/Mesh.cpp
    ../../src/stb_image.cpp
)

include_directories(
    ../../third_party/glfw/include
    ../../third_party/glad/include
    ../../third_party/glm
    ../../include/third_party
    ../../include

)

target_link_libraries(cube_demo PRIVATE
    glfw
    glad
    PRIVATE TKernel TKMath TKG2d TKG3d TKGeomBase TKGeomAlgo TKBRep TKTopAlgo TKPrim
    TKSTEP TKSTEP209 TKSTEPBase TKSTEPAttr
    TKMesh
)