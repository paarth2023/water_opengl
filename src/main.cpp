#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "../renderer/Shader.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/BufferLayout.h"
#include "../renderer/VertexArray.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

unsigned int screen_width = 1280;
unsigned int screen_height = 720;

void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// struct Particle {
//     glm::vec3 center;
//     float radius;
//     glm::vec3 color;
//     // to be added -> density, velocity, etc.
// };

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "water", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR::WINDOW_INIT_FAILED" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD_INIT_FAILED" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, resize_callback);

    Shader ourShader("./shader_files/vertex.glsl", "./shader_files/fragment.glsl");

    std::vector<glm::vec3> points = {
        glm::vec3(-0.5, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f)};

    VertexBuffer vb(points.data(), points.size() * sizeof(glm::vec3));

    BufferLayout layout;
    layout.Push<float>(3);

    VertexArray va;
    va.AddBuffer(vb, layout);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(points.size()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}