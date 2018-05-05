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
        framebuffer = new unsigned char[height * width * 4];
        depthBuffer = new VkFloat[height * width];
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                depthBuffer[j * height + i] = -100.0f;
        backgroundColor = Color(1.0f, 1.0f, 1.0f);
        glfwInit(); // TODO: check init status
        glewInit();
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwMakeContextCurrent(window);
        camera = new Camera(0.0f, 0.0f, 3.0f);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);

        drawMode = DRAW_FACES;
        optimizationMode = 0;
    }
    // todo deep-copy

    VirtualDevice::~VirtualDevice() {
        delete[] framebuffer;
        delete[] depthBuffer;
        delete camera;
    }

    int VirtualDevice::getWidth() const { return width; }

    int VirtualDevice::getHeight() const { return height; }

    VkFloat *VirtualDevice::getDepth(int x, int y) {
        return &depthBuffer[y * width + x];
    }

    bool VirtualDevice::shouldShutdown() {
        return (bool) glfwWindowShouldClose(window);
    }

    void VirtualDevice::setBackgroundColor(float r, float g, float b) {
        //glClearColor(r,g,b, 1.0f);
        backgroundColor = Color(r, g, b);
    }

    void VirtualDevice::refreshBuffer() {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer);
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++) {
                depthBuffer[j * width + i] = 1.1f;
                drawPixel(i, j, backgroundColor);
            }
        glfwSwapBuffers(window);
    }

    void VirtualDevice::setDrawMode(VkModeCode modeCode, bool enabled) {
        if (enabled)
            drawMode |= modeCode;
        else
            drawMode &= ~modeCode;
    }

    void VirtualDevice::setOptimization(VkModeCode modeCode, bool enabled) {
        if (enabled)
            optimizationMode |= modeCode;
        else
            optimizationMode &= ~modeCode;
    }

    void VirtualDevice::bindTexture(Image::Texture *texture) {
        currentTexture = texture;
    }

    void VirtualDevice::drawPixel(int x, int y, Color color) {
        framebuffer[(y * width + x) * 4] = (unsigned char) lround(color.r * 255);
        framebuffer[(y * width + x) * 4 + 1] = (unsigned char) lround(color.g * 255);
        framebuffer[(y * width + x) * 4 + 2] = (unsigned char) lround(color.b * 255);
        framebuffer[(y * width + x) * 4 + 3] = (unsigned char) lround(color.a * 255);
    }

    void VirtualDevice::mainLoop() {
        glfwPollEvents();
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
        camera->updatePos(x, y, z);
        camera->updateView(pitch, yaw);
        Transform::currentTransform.setView(camera->viewMatrix());

        if (glfwGetKey(window, GLFW_KEY_O))
            Transform::currentTransform.setModel(
                    rotate(2.0f, Vector(0.0f, 1.0f, 0.0f)) * Transform::currentTransform.getModel());
        if (glfwGetKey(window, GLFW_KEY_P))
            Transform::currentTransform.setModel(
                    rotate(-2.0f, Vector(0.0f, 1.0f, 0.0f)) * Transform::currentTransform.getModel());

        // set mode
        if (glfwGetKey(window, GLFW_KEY_Z))
            setDrawMode(DRAW_BORDERS, true);
        if (glfwGetKey(window, GLFW_KEY_X))
            setDrawMode(DRAW_BORDERS, false);
        if (glfwGetKey(window, GLFW_KEY_C))
            setDrawMode(DRAW_FACES, true);
        if (glfwGetKey(window, GLFW_KEY_V))
            setDrawMode(DRAW_FACES, false);
        if (glfwGetKey(window, GLFW_KEY_B))
            setDrawMode(DRAW_TEXTURE, true);
        if (glfwGetKey(window, GLFW_KEY_N))
            setDrawMode(DRAW_TEXTURE, false);
        if (glfwGetKey(window, GLFW_KEY_T))
            setOptimization(FACE_CULLING, true);
        if (glfwGetKey(window, GLFW_KEY_Y))
            setOptimization(FACE_CULLING, false);
    }
}