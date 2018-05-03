//
// Created by jeff2310 on 4/26/18.
//

#include "Texture.h"

namespace Image {
    Texture::Texture() : image(nullptr) {}

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
}