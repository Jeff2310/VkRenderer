//
// Created by jeff2310 on 4/18/18.
//

#ifndef VKSOFTWARERENDER_VIRTUALDEVICE_H
#define VKSOFTWARERENDER_VIRTUALDEVICE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "MathUtility.h"
#include "Primitives.h"
#include "Camera.h"

using namespace std;

namespace VkRenderer {
    typedef float VkFloat;
    typedef uint VkUint;

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

        explicit VirtualDevice(const string &name, VkUint width = 1, VkUint height = 1);
        // todo deep-copy

        ~VirtualDevice();

        int getWidth() const;

        int getHeight() const;

        VkFloat *getDepth(int x, int y);

        bool shouldShutdown();

        void setBackgroundColor(float r, float g, float b);

        void refreshBuffer();

        void drawPixel(int x, int y, Color color);

        void mainLoop();
    };
}

#endif //VKSOFTWARERENDER_VIRTUALDEVICE_H
