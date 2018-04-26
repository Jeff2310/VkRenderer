//
// Created by jeff2310 on 4/18/18.
//

#ifndef VKSOFTWARERENDER_VIRTUALDEVICE_H
#define VKSOFTWARERENDER_VIRTUALDEVICE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "MathUtility.h"
#include "Camera.h"

using namespace std;

namespace VkRenderer {
#define DRAW_FACES 1
#define DRAW_BORDERS 2
#define DRAW_DEPTH 3

    typedef float VkFloat;
    typedef uint VkUint;
    typedef unsigned char VkModeCode;

    class VirtualDevice {
    private:
        string name;
        //pixels中行从y较大的方向开始存
        char *framebuffer;
        VkFloat *depthBuffer;
        VkFloat *stencilBuffer;
        VkUint width, height;
        GLFWwindow *window;
        Color backgroundColor;


    public:
        Camera *camera;
        VkModeCode drawMode;

        explicit VirtualDevice(const string &name, VkUint width = 1, VkUint height = 1);
        // todo deep-copy

        ~VirtualDevice();

        int getWidth() const;

        int getHeight() const;

        VkFloat *getDepth(int x, int y);

        bool shouldShutdown();

        void setBackgroundColor(float r, float g, float b);

        void refreshBuffer();

        void setMode(VkModeCode modeCode, bool enabled);

        void drawPixel(int x, int y, Color color);

        void mainLoop();
    };
}

#endif //VKSOFTWARERENDER_VIRTUALDEVICE_H
