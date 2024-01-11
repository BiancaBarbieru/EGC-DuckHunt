#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        void Init() override;

     private:
        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4& modelMatrix) override;
        void RenderMesh1(Mesh *mesh, Shader *shader, const glm::mat4& modelMatrix);
        void FrameStart() override;
        void RenderScene();
        void RenderScene1();
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void Tree(glm::vec3 treePosition);
        void Tree1(glm::vec3 treePosition);

     protected:
        implemented::Camera *camera, *camera1;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        ViewportArea miniViewportArea;

        // TODO(student): If you need any other class variables, define them here.
        float bottom, top, zNear, zFar, left, right, fov, aspect;
        glm::vec3 up, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17;
        glm::vec3 diff0, diff1, diff2, diff3, diff4, diff5, diff6, diff7, diff8, diff9, diff10, diff11, diff12, diff13, diff14, diff15, diff16, diff17;
        float distR, distA;
        glm::vec3 a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v;
        glm::vec3 treePosition;
        std::vector<glm::vec3> positionTree;
        std::vector<glm::vec3> positionTree1;
        float cameraVar;


    };
}   // namespace m1
