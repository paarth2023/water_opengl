#include "./CircleRenderer.h"

CircleRenderer::CircleRenderer()
{
}

CircleRenderer::~CircleRenderer() {}

void createCircle(CircleGeometry &givenCircle, int segments, std::vector<CircleInstance> &storage)
{
    float angle = 360.0f / segments;
    for (int i = 0; i < segments; i++)
    {
        storage.push_back({glm::vec3(givenCircle.center.x, givenCircle.center.y, 0.0f), givenCircle.color, givenCircle.translation});
        float xi = givenCircle.center.x + givenCircle.radius * cos(glm::radians(i * angle));
        float yi = givenCircle.center.y + givenCircle.radius * sin(glm::radians(i * angle));
        storage.push_back({glm::vec3(xi, yi, 0.0f), givenCircle.color, givenCircle.translation});
        float xip1 = givenCircle.center.x + givenCircle.radius * cos(glm::radians(((i + 1) % segments) * angle));
        float yip1 = givenCircle.center.y + givenCircle.radius * sin(glm::radians(((i + 1) % segments) * angle));
        storage.push_back({glm::vec3(xip1, yip1, 0.0f), givenCircle.color, givenCircle.translation});
    }
}

void CircleRenderer::Init(std::vector<CircleGeometry> &givenCircles, int segments)
{
    for (int i = 0; i < givenCircles.size(); i++)
    {
        createCircle(givenCircles[i], segments, points);
    }
    vb.Init(points.data(), points.size() * sizeof(CircleInstance));
    bl.Push<float>(3);
    bl.Push<float>(3);
    bl.Push<float>(3);
    va.AddBuffer(vb, bl);
}

void CircleRenderer::Draw()
{
    va.Bind();
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(points.size()));
}
