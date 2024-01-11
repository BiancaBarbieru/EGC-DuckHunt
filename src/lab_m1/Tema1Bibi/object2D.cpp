#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        //VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length/2, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

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

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        //VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(length + 7, length - 10, 0), color)
    };

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}


Mesh* object2D::CreateBody(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        //VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, length + length, 0), color),
        VertexFormat(corner + glm::vec3(length * 3.2, length - length / 10, 0), color)
    };

    Mesh* body = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        body->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices, indices);
    return body;

}

Mesh* object2D::CreateWing(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(-length/2, length * 2 / sqrt(3), 0), color),
        VertexFormat(corner + glm::vec3(length/2, length * 2 / sqrt(3), 0), color),
        //VertexFormat(corner + glm::vec3(0, length + length, 0), color),
        //VertexFormat(corner + glm::vec3(length, length * 2 / sqrt(3), 0), color)
    };

    Mesh* wing = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        wing->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    wing->InitFromData(vertices, indices);
    return wing;

}

Mesh* object2D::CreateWindow(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(1, 0, 0), color),
        VertexFormat(corner + glm::vec3(length - 1, 0, 0), color),
        VertexFormat(corner + glm::vec3(length - 1, length - 560, 0), color),
        VertexFormat(corner + glm::vec3(0, length - 560, 0), color)
    };

    Mesh* cWindow = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        cWindow->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    cWindow->InitFromData(vertices, indices);
    return cWindow;

}

Mesh* object2D::CreateShoot(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(1, 0, 0), color),
        VertexFormat(corner + glm::vec3(length - 1, 0, 0), color),
        VertexFormat(corner + glm::vec3(length - 1, length * 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length * 2, 0), color)
    };

    Mesh* createShoot = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        createShoot->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    createShoot->InitFromData(vertices, indices);
    return createShoot;

}

Mesh* object2D::CreateScore(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color),
        VertexFormat(corner + glm::vec3(length * 2.5, 0, 0), color),
        VertexFormat(corner + glm::vec3(length * 2.5 , length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length / 2, 0), color)
    };

    Mesh* createScore = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        createScore->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    createScore->InitFromData(vertices, indices);
    return createScore;

}

Mesh* object2D::CreateScore1(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, 50, 0), color),
        VertexFormat(corner + glm::vec3(0, 50, 0), color)
    };

    Mesh* createScore1 = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        createScore1->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    createScore1->InitFromData(vertices, indices);
    return createScore1;

}

Mesh* object2D::CreateGrass(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(1, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length - 1100, 0), color),
        VertexFormat(corner + glm::vec3(0, length - 1100, 0), color)
    };

    Mesh* grass = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        grass->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    grass->InitFromData(vertices, indices);
    return grass;

}

Mesh* object2D::CreateBoxToShoot(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length - 180, length - 95, 0), color),
        VertexFormat(corner + glm::vec3(length + 57, length - 95, 0), color),
        VertexFormat(corner + glm::vec3(length + 57, length + 85, 0), color),
        VertexFormat(corner + glm::vec3(length - 180, length + 85, 0), color)
    };

    Mesh* boxToShoot = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        boxToShoot->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    boxToShoot->InitFromData(vertices, indices);
    return boxToShoot;

}
