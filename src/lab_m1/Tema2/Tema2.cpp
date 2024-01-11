#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/Tema2/transform3D.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    renderCameraTarget = false;
    bottom = -10;
    top = 10;
    zNear = 0.01f;
    zFar = 200.f;
    left = -10;
    right = 10;
    fov = RADIANS(60) - 0.5;
    aspect = window->props.aspectRatio;


    distR = 0.1f;
    distA = 0.8f;

    cameraVar = 0;

    treePosition = glm::vec3(0, 1, 0);

    camera = new implemented::Camera();
    camera->Set(glm::vec3(5.5f, 0.15f, 2.9f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->RotateFirstPerson_OY(0.2f);
    

    camera1 = new implemented::Camera();
    camera1->Set(glm::vec3(5.5f, 0, 2.9f), camera->GetTargetPosition(), glm::vec3(0, 0, 1));


    {
        //car
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0,  1), glm::vec3(0.2, 0.8, 0.6))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["box"] = new Mesh("generated box");
        meshes["box"]->InitFromData(vertices, indices);
    }

    //grass
    {
        Mesh* mesh = new Mesh("grass");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

    a = glm::vec3(4.86f, 0, 0.29f);
    b = glm::vec3(4.21f, 0, 1.40f);
    c = glm::vec3(2.79f, 0, 2.14f);
    d = glm::vec3(1.50f, 0, 1.95f);
    e = glm::vec3(0.59f, 0, 1.25f);
    f = glm::vec3(-0.45f, 0, 1.05f);
    g = glm::vec3(-1.76f, 0, 1.15f);
    h = glm::vec3(-2.83f, 0, 1.43f);
    i = glm::vec3(-3.79f, 0, 0.81f);
    j = glm::vec3(-3.93f, 0, -0.19f);
    k = glm::vec3(-3.45f, 0, -1.05f);
    l = glm::vec3(-2.11f, 0, -1.55f);
    m = glm::vec3(-0.68f, 0, -1.62f);
    n = glm::vec3(0.44f, 0, -0.98f);
    o = glm::vec3(1.35f, 0, -0.98f);
    p = glm::vec3(2.23f, 0, -0.69f);
    q = glm::vec3(3.49f, 0, -0.87f);
    r = glm::vec3(4.56f, 0, -0.40f);

    positionTree.push_back(a);
    positionTree.push_back(b);
    positionTree.push_back(c);
    positionTree.push_back(d);
    positionTree.push_back(e);
    positionTree.push_back(f);
    positionTree.push_back(g);
    positionTree.push_back(h);
    positionTree.push_back(i);
    positionTree.push_back(j);
    positionTree.push_back(k);
    positionTree.push_back(l);
    positionTree.push_back(m);
    positionTree.push_back(n);
    positionTree.push_back(o);
    positionTree.push_back(p);
    positionTree.push_back(q);
    positionTree.push_back(r);

    s = glm::vec3(-5.0f, 0, 2.0f);
    t = glm::vec3(4.98f, 0, 3.37f);
    u = glm::vec3(5.78f, 0, -1.61f);
    v = glm::vec3(-4.58f, 0, -2.9f);

    up = glm::vec3(0, 1, 0);

    diff0 = a - r;
    diff1 = b - a;
    diff2 = c - b;
    diff3 = d - c;
    diff4 = e - d;
    diff5 = f - e;
    diff6 = g - f;
    diff7 = h - g;
    diff8 = i - h;
    diff9 = j - i;
    diff10 = k - j;
    diff11 = l - k;
    diff12 = m - l;
    diff13 = n - m;
    diff14 = o - n;
    diff15 = p - o;
    diff16 = q - p;
    diff17 = r - q;


    p0 = cross(diff0, up);
    p1 = cross(diff1, up);
    p2 = cross(diff2, up);
    p3 = cross(diff3, up);
    p4 = cross(diff4, up);
    p5 = cross(diff5, up);
    p6 = cross(diff6, up);
    p7 = cross(diff7, up);
    p8 = cross(diff8, up);
    p9 = cross(diff9, up);
    p10 = cross(diff10, up);
    p11 = cross(diff11, up);
    p12 = cross(diff12, up);
    p13 = cross(diff13, up);
    p14 = cross(diff14, up);
    p15 = cross(diff15, up);
    p16 = cross(diff16, up);
    p17 = cross(diff17, up);

    positionTree1.push_back(p0);
    positionTree1.push_back(p1);
    positionTree1.push_back(p2);
    positionTree1.push_back(p3);
    positionTree1.push_back(p4);
    positionTree1.push_back(p5);
    positionTree1.push_back(p6);
    positionTree1.push_back(p7);
    positionTree1.push_back(p8);
    positionTree1.push_back(p9);
    positionTree1.push_back(p10);
    positionTree1.push_back(p11);
    positionTree1.push_back(p12);
    positionTree1.push_back(p13);
    positionTree1.push_back(p14);
    positionTree1.push_back(p15);
    positionTree1.push_back(p16);
    positionTree1.push_back(p17);


    //road
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(a - distA * p1, glm::vec3(0), glm::vec3(0, 0, 0)), //0
            VertexFormat(a + distR * p1, glm::vec3(0), glm::vec3(0, 0, 0)), //1
            VertexFormat(b - distA * p2, glm::vec3(0), glm::vec3(0, 0, 0)), //2
            VertexFormat(b + distR * p2, glm::vec3(0), glm::vec3(0, 0, 0)), //3
            VertexFormat(c - distA * p3, glm::vec3(0), glm::vec3(0, 0, 0)), //4
            VertexFormat(c + distR * p3, glm::vec3(0), glm::vec3(0, 0, 0)), //5
            VertexFormat(d - distA * p4, glm::vec3(0), glm::vec3(0, 0, 0)), //6
            VertexFormat(d + distR * p4, glm::vec3(0), glm::vec3(0, 0, 0)), //7
            VertexFormat(e - distA * p5, glm::vec3(0), glm::vec3(0, 0, 0)), //8
            VertexFormat(e + distR * p5, glm::vec3(0), glm::vec3(0, 0, 0)), //9
            VertexFormat(f - distA * p6, glm::vec3(0), glm::vec3(0, 0, 0)),//10
            VertexFormat(f + distR * p6, glm::vec3(0), glm::vec3(0, 0, 0)),//11
            VertexFormat(g - distA * p7, glm::vec3(0), glm::vec3(0, 0, 0)),//12
            VertexFormat(g + distR * p7, glm::vec3(0), glm::vec3(0, 0, 0)),//13
            VertexFormat(h - distA * p8, glm::vec3(0), glm::vec3(0, 0, 0)),//14
            VertexFormat(h + distR * p8, glm::vec3(0), glm::vec3(0, 0, 0)),//15
            VertexFormat(i - distA * p9, glm::vec3(0), glm::vec3(0, 0, 0)),//16
            VertexFormat(i + distR * p9, glm::vec3(0), glm::vec3(0, 0, 0)),//17
            VertexFormat(j - distA * p10, glm::vec3(0), glm::vec3(0, 0, 0)),//18
            VertexFormat(j + distR * p10, glm::vec3(0), glm::vec3(0, 0, 0)),//19
            VertexFormat(k - distA * p11, glm::vec3(0), glm::vec3(0, 0, 0)),//20
            VertexFormat(k + distR * p11, glm::vec3(0), glm::vec3(0, 0, 0)),//21
            VertexFormat(l - distA * p12, glm::vec3(0), glm::vec3(0, 0, 0)),//22
            VertexFormat(l + distR * p12, glm::vec3(0), glm::vec3(0, 0, 0)),//23
            VertexFormat(m - distA * p13, glm::vec3(0), glm::vec3(0, 0, 0)),//24
            VertexFormat(m + distR * p13, glm::vec3(0), glm::vec3(0, 0, 0)),//25
            VertexFormat(n - distA * p14, glm::vec3(0), glm::vec3(0, 0, 0)),//26
            VertexFormat(n + distR * p14, glm::vec3(0), glm::vec3(0, 0, 0)),//27
            VertexFormat(o - distA * p15, glm::vec3(0), glm::vec3(0, 0, 0)),//28
            VertexFormat(o + distR * p15, glm::vec3(0), glm::vec3(0, 0, 0)),//29
            VertexFormat(p - distA * p16, glm::vec3(0), glm::vec3(0, 0, 0)),//30
            VertexFormat(p + distR * p16, glm::vec3(0), glm::vec3(0, 0, 0)),//31
            VertexFormat(q - distA * p17, glm::vec3(0), glm::vec3(0, 0, 0)),//32
            VertexFormat(q + distR * p17, glm::vec3(0), glm::vec3(0, 0, 0)),//33
            VertexFormat(r - distA * p0, glm::vec3(0), glm::vec3(0, 0, 0)),//34
            VertexFormat(r + distR * p0, glm::vec3(0), glm::vec3(0, 0, 0)),//35
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 1, 3,
            2, 3, 4,
            4, 3, 5,
            4, 5, 6,
            6, 5, 7,
            6, 7, 8,
            8, 7, 9,
            8, 9, 10,
            10, 9, 11,
            10, 11, 12,
            12, 11, 13,
            12, 13, 14,
            14, 13, 15,
            14, 15, 16,
            16, 15, 17,
            16, 17, 18,
            18, 17, 19,
            18, 19, 20,
            20, 19, 21,
            20, 21, 22,
            22, 21, 23,
            22, 23, 24,
            24, 23, 25,
            24, 25, 26,
            26, 25, 27,
            26, 27, 28,
            28, 27, 29,
            28, 29, 30,
            30, 29, 31,
            30, 31, 32,
            32, 31, 33,
            32, 33, 34,
            34, 33, 35,
            34, 35, 0,
            0, 35, 1,
        };

        meshes["road"] = new Mesh("road1");
        meshes["road"]->InitFromData(vertices, indices);

    }
}


void Tema2::FrameStart()
{
    glClearColor(0.537f, 0.812f, 0.941f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

}

void Tema2::Tree(glm::vec3 treePosition) {
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["tree"] = new Mesh("generated tree");
        meshes["tree"]->InitFromData(vertices, indices);
    }




    {
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0))

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4

    };

    meshes["tree2"] = new Mesh("generated tree2");
    meshes["tree2"]->InitFromData(vertices, indices);
    }


    glm::mat4 modelMatrix3 = glm::mat4(1);
    modelMatrix3 = glm::translate(modelMatrix3, treePosition);
    modelMatrix3 = glm::scale(modelMatrix3, glm::vec3(0.3f, 0.3f, 0.3f));
    RenderMesh(meshes["tree"], shaders["VertexNormal"], modelMatrix3);

    glm::mat4 modelMatrix4 = glm::mat4(1);
    modelMatrix4 = glm::translate(modelMatrix4, treePosition + glm::vec3(0.09f, -0.3f, 0.09f));
    modelMatrix4 = glm::scale(modelMatrix4, glm::vec3(0.1f, 0.3f, 0.1f));
    RenderMesh(meshes["tree2"], shaders["VertexNormal"], modelMatrix4);

}

void Tema2::Tree1(glm::vec3 treePosition) {
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1), glm::vec3(0, 0.2f, 0.13f))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["tree"] = new Mesh("generated tree");
        meshes["tree"]->InitFromData(vertices, indices);
    }




    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1), glm::vec3(0.588f, 0.294f,  0))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["tree2"] = new Mesh("generated tree2");
        meshes["tree2"]->InitFromData(vertices, indices);
    }


    glm::mat4 modelMatrix3 = glm::mat4(1);
    modelMatrix3 = glm::translate(modelMatrix3, treePosition);
    modelMatrix3 = glm::scale(modelMatrix3, glm::vec3(0.3f, 0.3f, 0.3f));
    RenderMesh1(meshes["tree"], shaders["VertexNormal"], modelMatrix3);

    glm::mat4 modelMatrix4 = glm::mat4(1);
    modelMatrix4 = glm::translate(modelMatrix4, treePosition + glm::vec3(0.09f, -0.3f, 0.09f));
    modelMatrix4 = glm::scale(modelMatrix4, glm::vec3(0.1f, 0.3f, 0.1f));
    RenderMesh1(meshes["tree2"], shaders["VertexNormal"], modelMatrix4);

}

void Tema2::RenderScene() {

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix *= transform3D::Translate(0, -0.42f, 0);
    modelMatrix *= transform3D::RotateOY(cameraVar);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.1f, 0.1f));
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    glm::mat4 modelMatrix1 = glm::mat4(1);
    modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0.0101f, 0));
    RenderMesh(meshes["road"], shaders["VertexNormal"], modelMatrix1);

    glm::mat4 modelMatrix2 = glm::mat4(1);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0, 0.01f, 0));
    RenderMesh(meshes["grass"], shaders["VertexNormal"], modelMatrix2);

    //tree position
    for (int i = 0; i < positionTree.size(); i++) {
        if (i == 0) {
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) + 10 * distR * positionTree1[i]);
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.3f * distA * positionTree1[i]);
        }else if(i == 10 || i == 15) {
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) + 4 * distR * positionTree1[i]);
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.8f * distA * positionTree1[i]);
        }
        else {
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.3f * distA * positionTree1[i]);
            Tree(positionTree[i] + glm::vec3(0, 0.32f, 0) + 4 * distR * positionTree1[i]);
        }
    }
    

}

void Tema2::RenderScene1() {

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix *= transform3D::Translate(0, -0.42f, 0);
    modelMatrix *= transform3D::RotateOY(cameraVar);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.1f, 0.1f));
    RenderMesh1(meshes["box"], shaders["VertexNormal"], modelMatrix);

    glm::mat4 modelMatrix1 = glm::mat4(1);
    modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0.011f, 0));
    RenderMesh1(meshes["road"], shaders["VertexNormal"], modelMatrix1);

    glm::mat4 modelMatrix2 = glm::mat4(1);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0, 0.01f, 0));
    RenderMesh1(meshes["grass"], shaders["VertexNormal"], modelMatrix2);

    //tree position
    for (int i = 0; i < positionTree.size(); i++) {
        if (i == 0) {
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) + 10 * distR * positionTree1[i]);
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.3f * distA * positionTree1[i]);
        }
        else if (i == 10 || i == 15) {
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) + 4 * distR * positionTree1[i]);
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.8f * distA * positionTree1[i]);
        }
        else {
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) - 1.3f * distA * positionTree1[i]);
            Tree1(positionTree[i] + glm::vec3(0, 0.32f, 0) + 4 * distR * positionTree1[i]);
        }
    }


}


void Tema2::Update(float deltaTimeSeconds)
{

    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

    RenderScene();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    projectionMatrix = glm::ortho(-3.f, 3.f, -2.f, 2.f, 0.f, 200.f);
    camera1->Set(glm::vec3(5.5f, 20, 2.9f), camera->GetTargetPosition(), glm::vec3(0, 0, 1));

    RenderScene1();
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderMesh1(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Tema2::FrameEnd()
{
    
}



void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    
        float cameraSpeed = 2.0f;
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->KeyHold(GLFW_KEY_W)) {
            //Translate the camera forward
            camera->MoveForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            //Translate the camera to the left
            camera->RotateThirdPerson_OY(cameraSpeed * deltaTime);
            cameraVar += cameraSpeed * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            //Translate the camera backward
            camera->MoveForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            //Translate the camera to the right
            camera->RotateThirdPerson_OY(-cameraSpeed * deltaTime);
            cameraVar -= cameraSpeed * deltaTime;
        }

}


void Tema2::OnKeyPress(int key, int mods)
{
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            //camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            //camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
