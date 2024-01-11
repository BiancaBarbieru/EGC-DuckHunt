#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateTriangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float pointA,
    float pointB, 
    float pointC,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(pointA, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, pointB, 0), color),
        VertexFormat(corner + glm::vec3(0, 0, pointC), color),
        VertexFormat(corner + glm::vec3(pointA + 0.1, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, pointB + 0.1, 0), color),
        VertexFormat(corner + glm::vec3(0, 0, pointC + 0.1), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}