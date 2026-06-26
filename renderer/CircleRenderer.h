#include <vector>
#include "./VertexArray.h"
#include "./VertexBuffer.h"
#include "./BufferLayout.h"
#include <glm/glm.hpp>

struct CircleGeometry
{
    glm::vec2 center;
    float radius;
};

struct CircleInstance
{
    glm::vec3 position;
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