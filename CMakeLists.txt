cmake_minimum_required(VERSION 3.10)
project(3D_Rendering_Engine)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCASCADE REQUIRED)




add_subdirectory(third_party/glfw)




add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include ${OpenCASCADE_INCLUDE_DIR})


include_directories(
    third_party/glfw/include
    third_party/glad/include
    third_party/glm
    include/third_party
    include

)



add_executable(3D_Rendering_Engine
    src/main.cpp
    src/Shader.cpp
    src/Camera.cpp
    src/Renderer.cpp
    src/Mesh.cpp
    src/stb_image.cpp
)



target_link_libraries(3D_Rendering_Engine PRIVATE
    glfw
    glad
    PRIVATE TKernel TKMath TKG2d TKG3d TKGeomBase TKGeomAlgo TKBRep TKTopAlgo TKPrim
    TKSTEP TKSTEP209 TKSTEPBase TKSTEPAttr
    TKMesh  
)

add_subdirectory(demo)


