//
// Created by jeff2310 on 4/18/18.
//

#ifndef VKSOFTWARERENDER_VIRTUALDEVICE_H
#define VKSOFTWARERENDER_VIRTUALDEVICE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

namespace VkRenderer {
    typedef uint VkColor;
    typedef float VkFloat;
    typedef uint VkUint;

    class VirtualDevice {
    private:
        string name;
        //pixels中行从y较大的方向开始存
        char *framebuffer;
        VkFloat *zbuffer;
        VkUint width, height;
        GLFWwindow *window;

    public:
        VirtualDevice(string name, VkUint width = 1, VkUint height = 1) {
            this->width = width;
            this->height = height;
            framebuffer = new char[height*width*4];
            zbuffer = new VkFloat[height*width];
            for(int i=0; i<width; i++)
                for(int j=0; j<height; j++)
                    zbuffer[j*height+i] = -1.1f;
            glfwInit(); // TODO: check init status
            glewInit();
            window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
            glfwMakeContextCurrent(window);

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glViewport(0, 0, (GLsizei) width, (GLsizei) height);
        }
        // todo deep-copy

        ~VirtualDevice() {
            delete[] framebuffer;
            delete[] zbuffer;

        }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        VkColor getColor(float r, float g, float b, float a){
            VkColor color = 0;

            color = color | ((GLubyte)(r*255) << 24);
            color = color | ((GLubyte)(g*255) << 16);
            color = color | ((GLubyte)(b*255) << 8);
            color = color | (GLubyte)(a*255);

            return color;
        }

        void setBackgroundColor(float r, float g, float b){
            glClearColor(r,g,b, 1.0f);
            for(int i=0; i<width; i++){
                for(int j=0; j<height; j++){
                    drawPixel(i,j, -1.0f, getColor(r, g, b, 1.0f));
                }
            }
        }
        void refreshBuffer(){
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer);
            glfwSwapBuffers(window);
        }

        void drawPixel(int x, int y, float w, VkColor color);
    };
}

#endif //VKSOFTWARERENDER_VIRTUALDEVICE_H
