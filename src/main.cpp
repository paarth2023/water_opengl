#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "../renderer/shader.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/BufferLayout.h"
#include "../renderer/VertexArray.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int screen_width = 1280;
unsigned int screen_height = 720;

// global variables stating where the circle begins and other things.
// needed for gravity simulation.
float posY = 0.8f;
float velY = 0.0f;
float gravity = -1.5f;
float restitution = 1.0f;
float floorY = -1.0f;
float ballRadius = 0.2f;

void updatePhysics(float deltatime)
{
    velY += gravity * deltatime;
    posY += velY * deltatime;

    if (posY - ballRadius < floorY)
    {
        posY = floorY + ballRadius;
        velY = -velY * restitution;
    }
}

// setting up points for drawing a circle.
std::vector<glm::vec3> points;

void createCircle(int numPoints, float radius)
{
    float angle = (360.0f / numPoints);
    std::vector<glm::vec3> temp;
    for (int i = 0; i < numPoints; i++)
    {
        float x = radius * glm::cos(glm::radians(angle * i));
        float y = radius * glm::sin(glm::radians(angle * i));
        temp.push_back(glm::vec3(x, y, 0.0f));
    }

    for (int i = 0; i < numPoints - 2; i++)
    {
        points.push_back(temp[0]);
        points.push_back(temp[i + 1]);
        points.push_back(temp[(i + 2) % numPoints]);
    }
}

void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// callback for controlling restitution
void restitution_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_K)
        {
            restitution += 0.01f;
            if (restitution > 1.0f)
                restitution = 1.0f;
            std::cout << "Restitution increased to " << restitution << std::endl;
        }
        if (key == GLFW_KEY_J)
        {
            restitution -= 0.01f;
            if (restitution < 0.0f)
                restitution = 0.0f;
            std::cout << "Restitution decreased to " << restitution << std::endl;
        }
    }
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
    glfwSetKeyCallback(window, restitution_callback);

    Shader ourShader("./shader_files/vertex.glsl", "./shader_files/fragment.glsl");

    createCircle(512, ballRadius);

    VertexBuffer vb;
    vb.Init(points.data(), points.size() * sizeof(glm::vec3));

    BufferLayout layout;
    layout.Push<float>(3);

    VertexArray va;
    va.AddBuffer(vb, layout);

    float aspect = (float)screen_width / (float)screen_height;

    float lastTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, posY, 0.0f));
        float currTime = glfwGetTime();
        float delta_time = currTime - lastTime;
        lastTime = currTime;
        updatePhysics(delta_time);

        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(points.size()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}