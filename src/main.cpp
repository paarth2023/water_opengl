#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "../renderer/Shader.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/BufferLayout.h"
#include "../renderer/VertexArray.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../renderer/CircleRenderer.h"

unsigned int screen_width = 1280;
unsigned int screen_height = 720;

void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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

    CircleRenderer cr;
    std::vector<CircleGeometry> circles;

    circles.push_back({glm::vec2(-0.5f, 0.0f), 0.02f, glm::vec3(1.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 0.0f, 0.0f)});

    cr.Init(circles, 8);

    float aspect = (float)screen_width / (float)screen_height;

    float lastTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);

        cr.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
