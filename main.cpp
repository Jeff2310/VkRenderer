#include "GeometryStage.h"
#include "Rasterisation.h"
#include "TextureLoader/Texture.h"
#include "TextureLoader/TextureLoader.h"

using namespace VkRenderer;

using namespace std;

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
    Transform::currentTransform.setView(
            getView(Vector(0.0f, 0.0f, 1.5f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)));
    Transform::currentTransform.setProjection(getPerspective(45.0f, 1.0f, 0.1f, 100.0f));

    device.setDrawMode(DRAW_BORDERS, false);
    device.setDrawMode(DRAW_FACES, true);
    device.setOptimization(FACE_CULLING, true);

    Image::Texture test(SPHERE_TEXTURE, SAMPLE_FILTER_LINEAR);
    Image::TextureLoader loader;
    loader.loadTextureChar(&test, "../earth_texture.png", PNG, RGBA);
    device.bindTexture(&test);

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

    device.refreshBuffer();
    return 0;
}