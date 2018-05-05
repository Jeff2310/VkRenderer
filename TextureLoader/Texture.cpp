//
// Created by jeff2310 on 4/26/18.
//

#include "Texture.h"
//#include <iostream>
#include <cmath>

//using namespace std;

namespace Image {
    Texture::Texture(TypeMode textureMode, TypeMode sampleMode) : image(nullptr), textureType(textureMode),
                                                                  sampleMode(sampleMode) {}

    Texture::~Texture() {
        if (image != nullptr) {
            delete image;
        }
    }

    unsigned int Texture::getWidth() {
        return width;
    }

    unsigned int Texture::getHeight() {
        return height;
    }

    void Texture::sample(float u, float v, void *colors) {
        // xy
        // 11:Left Bottom, 12: Left Top, 21: Right Bottom , 22: Right Top;
        int x1, x2, y1, y2;
        if (u > 1.0f) u = 1.0f;
        if (v > 1.0f) v = 1.0f;
        if (u < 0.0f) u = 0.0f;
        if (v < 0.0f) v = 0.0f;

        float x = u * (width - 1), y = v * (height - 1);
        x1 = (int) floorf(x), y1 = (int) floorf(y);
        x2 = x1 + 1, y2 = y1 + 1;
        if (x2 >= width) x2 = x1;
        if (y2 >= height) y2 = y1;

        // 到周围四个点的曼哈顿距离
        float distance[2][2];
        distance[0][0] = x - x1 + y - y1;
        distance[0][1] = x - x1 + y2 - y;
        distance[1][0] = x2 - x + y - y1;
        distance[1][1] = x2 - x + y2 - y;

//        cout<<x<<' '<<y<<endl;
        Color *currentSampleColor = (Color *) colors;

        if (sampleMode == SAMPLE_FILTER_NEAREST) {
            float min;
            Color *pointer = nullptr;

            min = distance[0][0], pointer = &image[(y1 * width + x1) * 4];
            if (distance[0][1] < min) min = distance[0][1], pointer = &image[(y2 * width + x1) * 4];
            if (distance[1][0] < min) min = distance[1][0], pointer = &image[(y1 * width + x2) * 4];
            if (distance[1][1] < min) pointer = &image[(y2 * width + x2) * 4];
            for (int i = 0; i < 4; i++)
                currentSampleColor[i] = pointer[i];
        } else if (sampleMode == SAMPLE_FILTER_LINEAR) {
            for (int i = 0; i < 4; i++) {
                currentSampleColor[i] = (Color) ((image[(y1 * width + x1) * 4 + i] + image[(y2 * width + x1) * 4 + i] +
                                                  image[(y1 * width + x2) * 4 + i] + image[(y2 * width + x2) * 4 + i]) /
                                                 4);
            }
        }
    }

    void Texture::projection(float *u, float *v) {
        if (textureType == CUBIC_TEXTURE) {
//            *u = *u;
//            *v = *v;
            return;
        } else if (textureType == SPHERE_TEXTURE) {
            *u = *u / (2 * 3.1415926f); // theta
//            *v = (*v / 3.1415926f) + 0.5f; // phi
            *v = 0.5f * sinf(*v) + 0.5f;
        }
    }
}