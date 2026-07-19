#include <vector>
#include "./VertexArray.h"
#include "./VertexBuffer.h"
#include "./BufferLayout.h"
#include <glm/glm.hpp>

struct CircleGeometry
{
    glm::vec2 center;
    float radius;
    glm::vec3 color;
    glm::vec3 translation;
};

struct CircleInstance
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 translation;
};

class CircleRenderer
{
    VertexBuffer vb;
    VertexArray va;
    BufferLayout bl;
    std::vector<CircleInstance> points;

public:
    CircleRenderer();
    ~CircleRenderer();
    void Init(std::vector<CircleGeometry> &givenCircles, int segments);
    void Draw();
};