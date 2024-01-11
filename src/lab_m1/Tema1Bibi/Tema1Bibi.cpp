#include "lab_m1/Tema1Bibi/Tema1Bibi.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1Bibi/transform2D.h"
#include "lab_m1/Tema1Bibi/object2D.h"
#include <time.h>

using namespace std;
using namespace m1;



/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1Bibi::Tema1Bibi()
{
}


Tema1Bibi::~Tema1Bibi()
{
}


void Tema1Bibi::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    beakSide = 25;
    circleSide = 25;
    eyeSide = 3;
    bodySide = 50;
    wingSide = 65;
    positionUR = false;
    positionUL = false;
    positionDL = false;
    positionDR = false;
    //random function for choosing when the duck fly if she fly to right or left
    leftOrRight = rand() % (2 - 1 + 1) + 1;
    if (leftOrRight == 1) {
        xPlus = true;
        yPlus = true;
        positionUR = true;
    }
    else if (leftOrRight == 2) {
        xPlus = false;
        yPlus = true;
        positionUL = true;
    }

    duckAlive = true;
    duckEscape = false;
    boxForShootSide = 0;

    //random function to choose from which point on ground the duck flies
    duckX = rand() % (1150 - 1 + 1) + 1;
    duckY = 0;

    wingR = 0;
    wingL = 0;
    windowWidth = 1280;
    windowHeight = 715;
    scoreVariable = 0;
    grassSide = 1280;
    shoot = 3;
    lives = 3;
    livesMaxim = 3;
    timer = 0;
    noDucks = 1;
    speed = 100;
    game = true;
    gameX = 640;
    gameY = 360;
    randomX1 = rand() % (5 - 2 + 1) + 2;
    randomY1 = rand() % (5 - 2 + 1) + 2;

    // Initialize angularStep
    angularStep = 0;

    //mesh for box to shot
    Mesh* boxToShoot = object2D::CreateBoxToShoot("boxToShoot", corner, boxForShootSide, glm::vec3(0, 0, 0), false);
    AddMeshToList(boxToShoot);

    //mesh beak
    Mesh* beak = object2D::CreateSquare("beak", corner, beakSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(beak);

    //mesh eye
    Mesh* eye = object2D::CreateCircle("eye", corner, eyeSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(eye);

    //mesh head
    Mesh* circle = object2D::CreateCircle("circle", corner, circleSide, glm::vec3(0.7, 0.4, 0.1), true);
    AddMeshToList(circle);

    //mesh body
    Mesh* body = object2D::CreateBody("body", corner, bodySide, glm::vec3(0.7, 0.4, 0.1), true);
    AddMeshToList(body);

    //meshes for wings
    Mesh* wing1 = object2D::CreateWing("wing1", corner, wingSide, glm::vec3(0.7, 0.4, 0.1), true);
    AddMeshToList(wing1);
    Mesh* wing2 = object2D::CreateWing("wing2", corner, wingSide, glm::vec3(0.7, 0.4, 0.1), true);
    AddMeshToList(wing2);

    //mesh box
    Mesh* cWindow = object2D::CreateWindow("cWindow", corner, windowWidth, glm::vec3(0.56, 0.89,	0.93), true);
    AddMeshToList(cWindow);

    //meshes for lives
    Mesh* live1 = object2D::CreateCircle("live1", corner, 10, glm::vec3(1, 0, 0), true);
    AddMeshToList(live1);

    //meshes for shoots
    Mesh* shoot1 = object2D::CreateShoot("shoot1", corner, 15, glm::vec3(0, 0.51, 0.25), false);
    AddMeshToList(shoot1);

    //meshes for score
    Mesh* score1 = object2D::CreateScore("score1", corner, 100, glm::vec3(0, 0, 1), false);
    AddMeshToList(score1);
    

    //mesh grass
    Mesh* grass = object2D::CreateGrass("grass", corner, grassSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(grass); 
}


void Tema1Bibi::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1Bibi::Update(float deltaTimeSeconds)
{
    //increment the speed after 5 ducks
    if (noDucks >= 5)
    {
        speed += 50;
        noDucks = 0;
    }

    //box for shoot
    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckX, duckY);
    RenderMesh2D(meshes["boxToShoot"], shaders["VertexColor"], modelMatrix);*/

    //grass
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    //at 5 seconds after one duck apears the duck escapes
    timer += deltaTimeSeconds;
    if (timer >= 5) {
        duckEscape = true;
        positionUR = false;
        positionUL = false;
        positionDL = false;
        positionDR = false;
    }

    //duck wings
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckX - 100, duckY + 10);
    if (duckEscape) {
        modelMatrix *= transform2D::Translate(30, -80);
        modelMatrix *= transform2D::Rotate(-1.57);
    }
    if (!duckAlive) {
        modelMatrix *= transform2D::Translate(62, 18);
        modelMatrix *= transform2D::Rotate(-1.57);
    }
    if (positionUR) {
        modelMatrix *= transform2D::Rotate(0.67);
        modelMatrix *= transform2D::Translate(25, -40);
    }
    if (positionUL) {
        modelMatrix *= transform2D::Translate(45, -37);
        modelMatrix *= transform2D::Rotate(-0.67);
    }
    if (positionDL) {
        modelMatrix *= transform2D::Translate(60, 0);
        modelMatrix *= transform2D::Rotate(-2.35);
    }
    if (positionDR) {
        modelMatrix *= transform2D::Translate(43, 13);
        modelMatrix *= transform2D::Rotate(-0.78);
    }                   
    {
            if(wingR < 30)
            modelMatrix *= transform2D::Rotate(0.5);
            else
            modelMatrix *= transform2D::Rotate(-0.5);
            wingR++;
            if (wingR > 60) wingR = 0;
    }
    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckX - 100, duckY - 20);
    if (duckEscape) {                              
        modelMatrix *= transform2D::Translate(10, -55);
        modelMatrix *= transform2D::Rotate(1.57);
    }
    if (!duckAlive) {
        modelMatrix *= transform2D::Translate(30, 45);
        modelMatrix *= transform2D::Rotate(1.57);
    }
    if (positionUR) {
        modelMatrix *= transform2D::Translate(60, 0);
        modelMatrix *= transform2D::Rotate(-2.35);
    }
    if (positionUL) {
        modelMatrix *= transform2D::Translate(30, -20);
        modelMatrix *= transform2D::Rotate(2.36);
    }
    if (positionDL) {
        modelMatrix *= transform2D::Translate(35, 50);
        modelMatrix *= transform2D::Rotate(0.67);
    }
    if (positionDR) {
        modelMatrix *= transform2D::Translate(20, 30);
        modelMatrix *= transform2D::Rotate(2.35);
    }
    {
        if (wingL < 30)
            modelMatrix *= transform2D::Rotate(-0.5);
        else
            modelMatrix *= transform2D::Rotate(0.5);
        wingL++;
        if (wingL > 60) wingL = 0;
    }
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrix);

    //duck beak
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckX + 35, duckY - 15);
    if (duckEscape) {
        modelMatrix *= transform2D::Translate(-97, 47);
        modelMatrix *= transform2D::Rotate(1.57);
    }
    if (!duckAlive) {
        modelMatrix *= transform2D::Translate(-100, -83);
        modelMatrix *= transform2D::Rotate(-1.57);
    }
    if (positionUR) {
        modelMatrix *= transform2D::Rotate(0.67);
        modelMatrix *= transform2D::Translate(53, 50);
    }
    if (positionUL) {
        modelMatrix *= transform2D::Translate(-180, 80);
        modelMatrix *= transform2D::Rotate(2.36);    
    }
    if (positionDL) {
        modelMatrix *= transform2D::Translate(-197, -40);
        modelMatrix *= transform2D::Rotate(-2.36);
    }
    if (positionDR) {
        modelMatrix *= transform2D::Translate(-20, -65);
        modelMatrix *= transform2D::Rotate(-0.78);
    }
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

    //duck eye
    for (int i = 0; i < 44; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckX + 20, duckY + 15);
        if (duckEscape) {
            modelMatrix *= transform2D::Translate(-77, 0);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (!duckAlive) {
            modelMatrix *= transform2D::Translate(-95, -90);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionUR) {
            modelMatrix *= transform2D::Translate(-10, 50);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionUL) {
            modelMatrix *= transform2D::Translate(-140, 40);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionDL) {
            modelMatrix *= transform2D::Translate(-170, -50);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionDR) {
            modelMatrix *= transform2D::Translate(-2, -47);
            modelMatrix *= transform2D::Rotate(i);
        }
        RenderMesh2D(meshes["eye"], shaders["VertexColor"], modelMatrix);
    }

    //duck head
    for (int i = 0; i < 44; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckX, duckY);
        if (duckEscape) {
            modelMatrix *= transform2D::Translate(-77, 0);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (!duckAlive) {
            modelMatrix *= transform2D::Translate(-55, -65);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionUR) {
            modelMatrix *= transform2D::Translate(15, 45);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionUL) {
            modelMatrix *= transform2D::Translate(-130, 35);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionDL) {
            modelMatrix *= transform2D::Translate(-127, -43);
            modelMatrix *= transform2D::Rotate(i);
        }
        if (positionDR) {
            modelMatrix *= transform2D::Translate(-2, -47);
            modelMatrix *= transform2D::Rotate(i);
        }
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
    }

    //duck body
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckX - 180, duckY - 50);
    if (duckEscape) {
        modelMatrix *= transform2D::Rotate(1.57);
        modelMatrix *= transform2D::Translate(-100, -150);
    }
    if (!duckAlive) {
        modelMatrix *= transform2D::Rotate(-1.57);
        modelMatrix *= transform2D::Translate(-160, 80);
    }
    if (positionUR) {
        modelMatrix *= transform2D::Rotate(0.78);
        modelMatrix *= transform2D::Translate(30, -115);
    }
    if (positionUL) {
        modelMatrix *= transform2D::Rotate(2.36);
        modelMatrix *= transform2D::Translate(-160, -140);
    }
    if (positionDL) {
        modelMatrix *= transform2D::Translate(150, 160);
        modelMatrix *= transform2D::Rotate(-2.36);
    }
    if (positionDR) {
        modelMatrix *= transform2D::Translate(20, 90);
        modelMatrix *= transform2D::Rotate(-0.78);
    }    
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    //duck movement
    movingDuck(deltaTimeSeconds);

    //duck lives
    for (int q = 0; q <
        livesMaxim; q++) {
        for (int i = 0; i < 44; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(25 + q * 50, 670);
            modelMatrix *= transform2D::Rotate(i);
            RenderMesh2D(meshes["live1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //shoots
    for (int o = 0; o < shoot; o++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(17 + o * 50, 610);
        RenderMesh2D(meshes["shoot1"], shaders["VertexColor"], modelMatrix);
    }

    //score
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 640);
    RenderMesh2D(meshes["score1"], shaders["VertexColor"], modelMatrix);

    Mesh* score2 = object2D::CreateScore1("score2", glm::vec3(0, 0, 0), scoreVariable, glm::vec3(0, 0, 1), true);
    AddMeshToList(score2);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 640);
    RenderMesh2D(meshes["score2"], shaders["VertexColor"], modelMatrix);

    //box
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["cWindow"], shaders["VertexColor"], modelMatrix);


}

void Tema1Bibi::movingDuck(float deltaTimeSeconds)
{

    if (game) {
        if (duckAlive && !duckEscape) {
            if (xPlus && yPlus && duckX < windowWidth && duckY < windowHeight)
            {
                duckY += randomY1 * speed * deltaTimeSeconds;
                duckX += randomX1 * speed * deltaTimeSeconds;
            }
            else
            {
                if (duckY >= windowHeight) yPlus = false;

                if (duckX >= windowWidth) xPlus = false;

                if (xPlus && !yPlus && duckX < windowWidth && duckY > 0)
                {
                    duckY -= randomY1 * speed * deltaTimeSeconds;
                    duckX += randomX1 * speed * deltaTimeSeconds;
                }
                else
                {
                    if (duckX >= windowWidth) xPlus = false;

                    if (duckY <= 0) yPlus = true;

                    if (duckX <= 0) xPlus = true;

                    if (!xPlus && !yPlus && duckY > 0 && duckX > 0)
                    {
                        duckY -= randomY1 * speed * deltaTimeSeconds;
                        duckX -= randomX1 * speed * deltaTimeSeconds;
                    }
                }
                if (yPlus && !xPlus && duckX > 0 && duckY < windowHeight)
                {
                    duckY += randomY1 * speed * deltaTimeSeconds;
                    duckX -= randomX1 * speed * deltaTimeSeconds;
                }
            }
            if (duckX <= 0 && (!xPlus && yPlus)) {
                positionUL = false;
                positionDL = false;
                positionDR = false;
                positionUR = true;
            }
            if (duckX <= 0 && (!xPlus && !yPlus)) {
                positionUL = false;
                positionDL = false;
                positionUR = false;
                positionDR = true;
            }
            if (duckX >= windowWidth && (xPlus && yPlus)) {
                positionDR = false;
                positionDL = false;
                positionUR = false;
                positionUL = true;
            }
            if (duckX >= windowWidth && (xPlus && !yPlus)) {
                positionDR = false;
                positionUL = false;
                positionUR = false;
                positionDL = true;
            }
            if (duckY >= windowHeight && (xPlus && yPlus)) {
                positionDL = false;
                positionUL = false;
                positionUR = false;
                positionDR = true;
            }
            if (duckY >= windowHeight && (!xPlus && yPlus)) {
                positionDR = false;
                positionUL = false;
                positionUR = false;
                positionDL = true;
            }
            if (duckY <= 0 && (!xPlus && !yPlus)) {
                positionDR = false;
                positionDL = false;
                positionUR = false;
                positionUL = true;
            }
            if (duckY <= 0 && (xPlus && !yPlus)) {
                positionDR = false;
                positionDL = false;
                positionUL = false;
                positionUR = true;
            }
        }
        else if (!duckAlive && !duckEscape) {
            if (duckY > 0) duckY -= speed * 2 * deltaTimeSeconds;
            else {
                duckAlive = true;
                duckX = rand() % (1150 - 1 + 1) + 1;
                leftOrRight = rand() % (2 - 1 + 1) + 1;
                if (leftOrRight == 1) {
                    xPlus = true;
                    yPlus = true;
                    positionUR = true;
                }
                else if (leftOrRight == 2) {
                    xPlus = false;
                    yPlus = true;
                    positionUL = true;
                }
                noDucks++;
            }
        }
        else if (duckAlive && duckEscape) {
            duckY += speed * 2 * deltaTimeSeconds;
            if (duckY >= windowHeight) {
                duckY = 0;
                timer = 0;
                duckEscape = false;
                leftOrRight = rand() % (2 - 1 + 1) + 1;
                if (leftOrRight == 1) {
                    xPlus = true;
                    yPlus = true;
                    positionUR = true;
                }
                else if (leftOrRight == 2) {
                    xPlus = false;
                    yPlus = true;
                    positionUL = true;
                }
                livesMaxim--;
                if (livesMaxim <= 0)
                    shoot = 0;
                else shoot = 3;
                noDucks++;
                if (livesMaxim == 0) {
                    game = false;
                    duckX = gameX;
                    duckY = gameY;
                }
            }
        }
    }
}


void Tema1Bibi::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1Bibi::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1Bibi::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1Bibi::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1Bibi::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //function to get the (0, 0) from up-left to down-left
    glm::ivec2 resolution = window->GetResolution();
    intersectionX = mouseX * 1280 / resolution.x;
    intersectionY = 720 - mouseY * 720 / resolution.y; 
}


void Tema1Bibi::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // if the bullets went down to 0 but the player still have lives the bullets will reload
    if (shoot == 0 && livesMaxim > 0) {
        shoot = 3;
    }
    //if the duck is alive and did not escaped and the player still have bullets the player can shoot
    if (duckAlive && !duckEscape && shoot > 0) {
        shoot--;
        //if the player shoots the duck...
        if ((intersectionX > duckX - 180 && intersectionX < duckX + 57) && (intersectionY > duckY - 95 && intersectionY < duckY + 85))
        {
            //...the score is going up
            if (scoreVariable <= 225)
                scoreVariable += 25;
            //the duck is dead
            duckAlive = false;
            //the position will be choosen when apears another duck
            positionUR = false;
            positionUL = false;
            positionDL = false;
            positionDR = false;
            //the timer is going to 0 beacause it will grow again when a new duck will apear
            timer = 0;
            //the bullets are full because a new duck will apear
            shoot = 3;
        }
    }
    //if the player miss with 3 consecutive bullets the duck, the duck will escape
    if (shoot == 0) {
        duckEscape = true;
        positionUR = false;
        positionUL = false;
        positionDL = false;
        positionDR = false;
    }
    //the score will get to 0 if it is maxim
    if (scoreVariable > 225) {
        scoreVariable = 0;
    }
}


void Tema1Bibi::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1Bibi::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1Bibi::OnWindowResize(int width, int height)
{
}
