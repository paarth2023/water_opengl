#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "../renderer/Shader.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/BufferLayout.h"
#include "../renderer/VertexArray.h"
#include "../renderer/CircleMesh.h"
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
    Shader newShader("./shader_files/circle_vertex.glsl", "./shader_files/circle_fragment.glsl");

    float radius = 0.02f;
    glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);

    Particle start = {
        glm::vec3(-0.25f, 0.0f, 0.0f),
        radius,
        color};
    float width = 0.5f;
    float height = 0.75f;
    float spacing = 0.02f;
    std::vector<Particle> particles; 
    Particle temp;
    float x_end = start.center.x + width;
    float y_end = start.center.y + height;
    for (float x = start.center.x; x <= x_end; x += spacing) {
        for (float y = start.center.y; y <= y_end; y += spacing) {
            temp = {glm::vec3(x, y, 0.0f), radius, color};
            particles.push_back(temp);
        }
    }
    VertexBuffer vb1(particles.data(), particles.size() * sizeof(Particle));
    BufferLayout layout1;
    layout1.Push<float>(3);
    layout1.Push<float>(1);
    layout1.Push<float>(3);
    VertexArray va1;
    va1.AddBuffer(vb1, layout1);
    // std::vector<glm::vec3> points = {
    //     glm::vec3(-0.5, 0.0f, 0.0f),
    //     glm::vec3(0.0f, 0.5f, 0.0f),
    //     glm::vec3(0.5f, 0.0f, 0.0f)};
    // VertexBuffer vb(points.data(), points.size() * sizeof(glm::vec3));

    // BufferLayout layout;
    // layout.Push<float>(3);

    // VertexArray va;
    // va.AddBuffer(vb, layout);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1. Global State Configuration
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // 2. DRAW PARTICLES
        newShader.use();
        // If your shader uses matrices, set them here:
        // newShader.setMat4("u_projection", projectionMatrix);
        va1.Bind();
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(particles.size()));

        // 3. DRAW TRIANGLES
        // ourShader.use();
        // va.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(points.size()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}