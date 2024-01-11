#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1Bibi : public gfxc::SimpleScene
    {
     public:
        Tema1Bibi();
        ~Tema1Bibi();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void movingDuck(float deltaTimeSeconds);
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        float angularStep;
        int wingL, wingR;
        float duckX, duckY;
        float windowWidth, windowHeight;
        float randomX, randomY;
        bool xPlus, yPlus;
        float beakSide, circleSide, eyeSide, bodySide, wingSide, grassSide;
        int shoot, lives, livesMaxim, scoreVariable, boxForShootSide, leftOrRight;
        bool duckAlive, duckEscape;
        float intersectionX, intersectionY;
        float timer;
        int noDucks, speed;
        bool game;
        int gameX, gameY;
        float randomX1, randomY1;
        bool positionUR, positionUL, positionDL, positionDR;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
