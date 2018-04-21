#include "GeometryStage.h"
#include "Rasterisation.h"
#include "Camera.h"

using namespace VkRenderer;

using namespace std;

Triangle singleColorTriangle(const Vector &p1, const Vector &p2, const Vector &p3, VkColor color) {
    Triangle t;
    t.p1.pos = p1;
    t.p2.pos = p2;
    t.p3.pos = p3;

    t.p1.color.r = t.p2.color.r = t.p3.color.r = (float) ((color & 0xFF000000) >> 24) / 255;
    t.p1.color.g = t.p2.color.g = t.p3.color.g = (float) ((color & 0x00FF0000) >> 16) / 255;
    t.p1.color.b = t.p2.color.b = t.p3.color.b = (float) ((color & 0x0000FF00) >> 8) / 255;
    t.p1.color.w = t.p2.color.w = t.p3.color.w = (float) ((color & 0x000000FF)) / 255;

    return t;
}

int main() {

    VirtualDevice device("test", 600, 600);


    Triangle front1 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                          Vector(0.0f, -0.5f, 1.0f), device.getColor(1.0f, 0.0f, 0.2f, 1.0f));

    Triangle front2 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(-0.5f, -0.5f, 1.0f),
                                          Vector(0.0f, -0.5f, 1.0f), device.getColor(1.0f, 0.0f, 0.2f, 1.0f));

    Triangle right1 = singleColorTriangle(Vector(0.0f, -0.5f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                          Vector(0.0f, 0.0f, 0.5f), device.getColor(0.2f, 1.0f, 0.0f, 1.0f));

    Triangle right2 = singleColorTriangle(Vector(0.0f, -0.5f, 1.0f), Vector(0.0f, -0.5f, 0.5f),
                                          Vector(0.0f, 0.0f, 0.5f), device.getColor(0.2f, 1.0f, 0.0f, 1.0f));

    Triangle up1 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                       Vector(0.0f, 0.0f, 0.5f), device.getColor(0.0f, 0.2f, 1.0f, 1.0f));

    Triangle up2 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(-0.5f, 0.0f, 0.5f),
                                       Vector(0.0f, 0.0f, 0.5f), device.getColor(0.0f, 0.2f, 1.0f, 1.0f));



    device.setBackgroundColor(0.3f, 0.58f, 0.80f);

    Transform::currentTransform.setModel(translate(0.0f, 0.0f, -2.0f));
    Transform::currentTransform.setView(
            getView(Vector(0.0f, 0.0f, 1.5f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)));
    Transform::currentTransform.setProjection(getPerspective(45.0f, 1.0f, 0.1f, 100.0f));

    while(!device.shouldShutdown()) {

        device.refreshBuffer();
        device.mainLoop();
        RenderTriangle(device, front1);
        RenderTriangle(device, front2);
        RenderTriangle(device, right1);
        RenderTriangle(device, right2);
        RenderTriangle(device, up1);
        RenderTriangle(device, up2);
        //RasterizeLine(device, 40, 80, 350, 240, 0.45f, black);
    }

    return 0;
}