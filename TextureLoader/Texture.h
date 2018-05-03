//
// Created by jeff2310 on 4/26/18.
//

#ifndef VKSOFTWARERENDER_TEXTURE_H
#define VKSOFTWARERENDER_TEXTURE_H

namespace Image {
    class Texture {
    private:
        unsigned int width, height;
//        unsigned char *image;
    public:
        friend class TextureLoader;

        Texture();

        ~Texture();

        unsigned int getWidth();

        unsigned int getHeight();

        unsigned char *image;
    };
}

#endif //VKSOFTWARERENDER_TEXTURE_H
