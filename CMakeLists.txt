cmake_minimum_required (VERSION 3.15)

project ("water")

include(FetchContent) # Loads the native online dependency engine


FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4  
    GIT_SHALLOW    ON   
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.3 
    GIT_SHALLOW    ON
)

FetchContent_MakeAvailable(glfw glm)

add_executable(water "src/main.cpp" "glad/src/glad.c"
    renderer/Shader.h
    renderer/Shader.cpp
    renderer/VertexBuffer.h
    renderer/VertexBuffer.cpp
    renderer/BufferLayout.h
    renderer/VertexArray.h
    renderer/VertexArray.cpp
    renderer/CircleRenderer.h
    renderer/CircleRenderer.cpp)

set_target_properties(water PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
)
target_include_directories(water PRIVATE "glad/include")

find_package(OpenGL REQUIRED)

target_link_libraries(water PRIVATE 
    glfw
    glm
    OpenGL::GL
)
