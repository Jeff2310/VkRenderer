//
// Created by jeff2310 on 4/26/18.
//

#include "TextureLoader.h"

#include <iostream>

using namespace std;


namespace Image {
    TextureLoader::TextureLoader() {
        FreeImage_Initialise();
    }

    TextureLoader::~TextureLoader() {
        FreeImage_DeInitialise();
    }

    void TextureLoader::loadTextureChar(Texture *texture, const char *path, ImageFormat imageFormat,
                                        PixelFormat pixelFormat) {
        FIBITMAP *bitmap = FreeImage_Load(imageFormat, path);
        if (bitmap == NULL) {
            // exceptions here
            return;
        }
        unsigned int dib = FreeImage_GetBPP(bitmap);
        unsigned int pixelSize = FreeImage_GetLine(bitmap) / FreeImage_GetWidth(bitmap);
        unsigned int width, height;
        width = FreeImage_GetWidth(bitmap), height = FreeImage_GetHeight(bitmap);

        texture->image = new unsigned char[width * height * pixelSize];
        texture->width = width;
        texture->height = height;

        BYTE *bytes = (BYTE *) FreeImage_GetBits(bitmap);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int i = 0; i < 4; i++) {
                    texture->image[(y * width + x) * pixelSize + i] = bytes[(y * width + x) * pixelSize + i];
                }
            }
        }

        FreeImage_Unload(bitmap);
    }
}