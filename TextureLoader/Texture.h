//
// Created by jeff2310 on 4/26/18.
//

#ifndef VKSOFTWARERENDER_TEXTURE_H
#define VKSOFTWARERENDER_TEXTURE_H

namespace Image {
#define SAMPLE_FILTER_NEAREST 1
#define SAMPLE_FILTER_LINEAR 2

#define CUBIC_TEXTURE 1
#define SPHERE_TEXTURE 2

    typedef unsigned char Color;
    typedef unsigned char TypeMode;
    class Texture {
    private:
        unsigned int width, height;
        Color *image;
        TypeMode sampleMode;
        TypeMode textureType;
    public:
        friend class TextureLoader;

        Texture(TypeMode textureMode, TypeMode sampleMode = SAMPLE_FILTER_NEAREST);

        ~Texture();

        unsigned int getWidth();

        unsigned int getHeight();

        void sample(float u, float v, void *colors);

        void projection(float *u, float *v);
    };
}

#endif //VKSOFTWARERENDER_TEXTURE_H
