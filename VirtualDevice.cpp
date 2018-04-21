//
// Created by jeff2310 on 4/15/18.
//

#include "VirtualDevice.h"
#include "Rasterisation.h"
#include "Camera.h"

namespace VkRenderer {
    VirtualDevice::VirtualDevice(const string &name, VkUint width, VkUint height) {
        this->width = width;
        this->height = height;
        framebuffer = new char[height * width * 4];
        zbuffer = new VkFloat[height * width];
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                zbuffer[j * height + i] = -100.0f;
        backgroundColor = 0xFFFFFFFF;
        glfwInit(); // TODO: check init status
        glewInit();
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwMakeContextCurrent(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    }
    // todo deep-copy

    VirtualDevice::~VirtualDevice() {
        delete[] framebuffer;
        delete[] zbuffer;

    }

    int VirtualDevice::getWidth() const { return width; }

    int VirtualDevice::getHeight() const { return height; }

    VkFloat *VirtualDevice::getDepth(int x, int y) {
        return &zbuffer[y * width + x];
    }

    bool VirtualDevice::shouldShutdown() {
        return (bool) glfwWindowShouldClose(window);
    }

    //TODO: change color definition to a independent from device;
    VkColor VirtualDevice::getColor(float r, float g, float b, float a) {
        VkColor color = 0;

        color = color | ((GLubyte) (r * 255) << 24);
        color = color | ((GLubyte) (g * 255) << 16);
        color = color | ((GLubyte) (b * 255) << 8);
        color = color | (GLubyte) (a * 255);

        return color;
    }

    void VirtualDevice::setBackgroundColor(float r, float g, float b) {
        //glClearColor(r,g,b, 1.0f);
        backgroundColor = getColor(r, g, b, 1.0f);
    }

    void VirtualDevice::refreshBuffer() {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer);
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++) {
                zbuffer[j * width + i] = 1.1f;
                drawPixel(i, j, backgroundColor);
            }
        glfwSwapBuffers(window);
    }

    void VirtualDevice::drawPixel(int x, int y, VkColor color) {
        char r, g, b, a;
        r = (char) ((color & 0xFF000000) >> 24),
        g = (char) ((color & 0x00FF0000) >> 16),
        b = (char) ((color & 0x0000FF00) >> 8),
        a = (char) ((color & 0x000000FF));
        framebuffer[(y * width + x) * 4] = r;
        framebuffer[(y * width + x) * 4 + 1] = g;
        framebuffer[(y * width + x) * 4 + 2] = b;
        framebuffer[(y * width + x) * 4 + 3] = a;
    }

    void VirtualDevice::mainLoop() {
        glfwPollEvents();
        // TODO:将Camera改为类的变量
        static Camera camera(0.0f, 0.0f, 0.0f);
        float x = 0.0f, y = 0.0f, z = 0.0f;
        float yaw = 0.0f, pitch = 0.0f;
        if (glfwGetKey(window, GLFW_KEY_A))
            x -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_D))
            x += 0.01f;
        if (glfwGetKey(window, GLFW_KEY_W))
            z -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_S))
            z += 0.01f;
        if (glfwGetKey(window, GLFW_KEY_Q))
            y += 0.01f;
        if (glfwGetKey(window, GLFW_KEY_E))
            y -= 0.01f;

        if (glfwGetKey(window, GLFW_KEY_J))
            yaw -= 2.0f;
        if (glfwGetKey(window, GLFW_KEY_L))
            yaw += 2.0f;
        if (glfwGetKey(window, GLFW_KEY_K))
            pitch += 2.0f;
        if (glfwGetKey(window, GLFW_KEY_I))
            pitch -= 2.0f;
        camera.updatePos(x, y, z);
        camera.updateView(pitch, yaw);
        Transform::currentTransform.setView(camera.viewMatrix());
    }
}