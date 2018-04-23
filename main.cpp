#include "GeometryStage.h"
#include "Rasterisation.h"
#include "Camera.h"

using namespace VkRenderer;

using namespace std;

Triangle singleColorTriangle(const Vector &p1, const Vector &p2, const Vector &p3, const Vector &normal, Color color) {
    Triangle t;
    t.p1.pos = p1;
    t.p2.pos = p2;
    t.p3.pos = p3;
    t.p1.normal = t.p2.normal = t.p3.normal = normal;
    t.p1.color = color;
    t.p2.color = color;
    t.p3.color = color;

    return t;
}

int main() {

    VirtualDevice device("test", 600, 600);


    Triangle front1 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                          Vector(0.0f, -0.5f, 1.0f),
                                          Vector(0.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 0.2f, 1.0f));

    Triangle front2 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(-0.5f, -0.5f, 1.0f),
                                          Vector(0.0f, -0.5f, 1.0f),
                                          Vector(0.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 0.2f, 1.0f));

    Triangle right1 = singleColorTriangle(Vector(0.0f, -0.5f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                          Vector(0.0f, 0.0f, 0.5f),
                                          Vector(1.0f, 0.0f, 0.0f), Color(0.2f, 1.0f, 0.0f, 1.0f));

    Triangle right2 = singleColorTriangle(Vector(0.0f, -0.5f, 1.0f), Vector(0.0f, -0.5f, 0.5f),
                                          Vector(0.0f, 0.0f, 0.5f),
                                          Vector(1.0f, 0.0f, 0.0f), Color(0.2f, 1.0f, 0.0f, 1.0f));

    Triangle up1 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f),
                                       Vector(0.0f, 0.0f, 0.5f),
                                       Vector(0.0f, 1.0f, 0.0f), Color(0.0f, 0.2f, 1.0f, 1.0f));

    Triangle up2 = singleColorTriangle(Vector(-0.5f, 0.0f, 1.0f), Vector(-0.5f, 0.0f, 0.5f),
                                       Vector(0.0f, 0.0f, 0.5f),
                                       Vector(0.0f, 1.0f, 0.0f), Color(0.0f, 0.2f, 1.0f, 1.0f));


    device.setBackgroundColor(0.3f, 0.58f, 0.80f);

    Transform::currentTransform.setModel(translate(0.0f, 0.0f, -2.0f));
    Transform::currentTransform.setView(
            getView(Vector(0.0f, 0.0f, 1.5f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)));
    Transform::currentTransform.setProjection(getPerspective(45.0f, 1.0f, 0.1f, 100.0f));

//    lightPos = Transform::currentTransform.applyTransform(lightPos);
//    lightPos = homogenize(device, lightPos);
//    lightPos = toViewport(device, lightPos);
//    device.phongVariable.lightPos = lightPos;

    while (!device.shouldShutdown()) {

        device.refreshBuffer();
        device.mainLoop();
        Transform::currentTransform.setModel(translate(0.0f, 0.0f, -2.0f) * scale(0.5f, 0.5f, 0.5f));
        RenderTriangle(device, front1);
        RenderTriangle(device, front2);
        RenderTriangle(device, right1);
        RenderTriangle(device, right2);
        RenderTriangle(device, up1);
        RenderTriangle(device, up2);

        Transform::currentTransform.setModel(translate(normalPhongVariable.lightPos) * scale(0.2f, 0.2f, 0.2f));
        RenderTriangle(device, up1);
        RenderTriangle(device, up2);
        //RasterizeLine(device, 40, 80, 350, 240, 0.45f, black);
    }

    return 0;
}