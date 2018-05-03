#include <iostream>
#include "GeometryStage.h"
#include "Rasterisation.h"
#include "TextureLoader/Texture.h"
#include "TextureLoader/TextureLoader.h"

using namespace VkRenderer;

using namespace std;

Vertex createVertex(const Vector &_pos, const Color &_color, const Vector &_normal) {
    PhongVariables variable;
    variable.fragPos = _pos;
    Vertex v(_pos, TextureCoordinate(), _color, _normal, variable);
    return v;
}

int main() {

    VirtualDevice device("test", 600, 600);

    Color colors[6] = {
            Color(1.0f, 0.0f, 0.2f, 1.0f),
            Color(1.0f, 0.0f, 0.2f, 1.0f),
            Color(0.2f, 1.0f, 0.0f, 1.0f),
            Color(0.2f, 1.0f, 0.0f, 1.0f),
            Color(0.0f, 0.2f, 1.0f, 1.0f),
            Color(0.0f, 0.2f, 1.0f, 1.0f)
    };

    Mesh cube = createCube(1.0f, colors);
    Mesh sphere = createSphere(0.5f, 15.0f);

    device.setBackgroundColor(0.3f, 0.58f, 0.80f);
//    device.setBackgroundColor(1.0f, 1.0f, 1.0f);
    Transform::currentTransform.setView(
            getView(Vector(0.0f, 0.0f, 1.5f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)));
    Transform::currentTransform.setProjection(getPerspective(45.0f, 1.0f, 0.1f, 100.0f));

    device.setDrawMode(DRAW_BORDERS, false);
    device.setDrawMode(DRAW_FACES, true);
    device.setOptimization(FACE_CULLING, true);

    while (!device.shouldShutdown()) {

        device.refreshBuffer();
        device.mainLoop();

//        Transform::currentTransform.setModel(translate(normalPhongConstants.lightPos) * scale(0.2f, 0.2f, 0.2f));
//        cube.render(device);
//
//        Transform::currentTransform.setModel(translate(0.0f, 0.0f, 0.0f));
//        cube.render(device);
        sphere.render(device);
    }

//    Image::Texture test;
//    Image::TextureLoader loader;
//    loader.loadTextureChar(&test, "../demo.png", PNG, RGBA);
//
//    int width = test.getWidth(), height = test.getHeight();
//    for(int x=0; x<width; x++){
//        for(int y=0; y<height; y++) {
//            // 这里默认是BGRA
//            device.framebuffer[(y * 600 + x) * 4 + 0] = test.image[(y * 600 + x) * 4 + 2];
//            device.framebuffer[(y * 600 + x) * 4 + 1] = test.image[(y * 600 + x) * 4 + 1];
//            device.framebuffer[(y * 600 + x) * 4 + 2] = test.image[(y * 600 + x) * 4 + 0];
//            device.framebuffer[(y * 600 + x) * 4 + 3] = test.image[(y * 600 + x) * 4 + 3];
//        }
//    }
//    device.refreshBuffer();
    return 0;
}