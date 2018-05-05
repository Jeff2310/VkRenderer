//
// Created by jeff2310 on 4/26/18.
//

#ifndef VKSOFTWARERENDER_TEXTURELOADER_H
#define VKSOFTWARERENDER_TEXTURELOADER_H

#include "Texture.h"
#include <FreeImage.h>

namespace Image {
#define PNG FIF_PNG
#define RGB 1
#define RGBA 2
    typedef FREE_IMAGE_FORMAT ImageFormat;
    typedef unsigned int PixelFormat;

    class TextureLoader {
    public:
        TextureLoader();

        ~TextureLoader();

        void loadTextureChar(Texture *texture, const char *path, ImageFormat imageFormat, PixelFormat pixelFormat);
    };
}

#endif //VKSOFTWARERENDER_TEXTURELOADER_H
