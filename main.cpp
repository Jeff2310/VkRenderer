#include "Rasterisation.h"
#include "VirtualDevice.h"

using namespace VkRenderer;

using namespace std;

int main() {

    VirtualDevice device("test", 400, 400);
    VkRenderer::VkColor white = device.getColor(1.0f, 1.0f, 1.0f, 1.0f);
    VkRenderer::VkColor black = device.getColor(0.0f, 0.0f, 0.0f, 1.0f);
    VkRenderer::VkColor mixed = device.getColor(1.0f, 0.0f, 0.0f, 1.0f);
    VkRenderer::VkColor blue = device.getColor(0.0f, 1.0f, 0.0f, 1.0f);


    Triangle t;
    t.p1.pos = Vector(160.0f, 350.0f, 0.5f);
    t.p1.color.r = 1.0f;
    t.p1.color.g = 0.0f;
    t.p1.color.b = 0.0f;
    t.p1.color.w = 1.0f;
    t.p2.pos = Vector(45.0f, 30.0f, 0.5f);
    t.p2.color.r = 0.0f;
    t.p2.color.g = 1.0f;
    t.p2.color.b = 0.0f;
    t.p2.color.w = 1.0f;
    t.p3.pos = Vector(380.0f, 100.0f, 0.5f);
    t.p3.color.r = 0.0f;
    t.p3.color.g = 0.0f;
    t.p3.color.b = 1.0f;
    t.p3.color.w = 1.0f;

    Triangle v;
    v.p1.pos = Vector(40.0f, 280.0f, 0.1f);
    v.p2.pos = Vector(265.0f, 30.0f, 0.65f);
    v.p3.pos = Vector(350.0f, 360.0f, 0.8f);
    v.p1.color.r = 0.0f;
    v.p1.color.g = 0.0f;
    v.p1.color.b = 1.0f;
    v.p1.color.w = 1.0f;
    v.p2.color.r = 1.0f;
    v.p2.color.g = 0.0f;
    v.p2.color.b = 0.0f;
    v.p2.color.w = 1.0f;
    v.p3.color.r = 0.0f;
    v.p3.color.g = 1.0f;
    v.p3.color.b = 0.0f;
    v.p3.color.w = 1.0f;
    /*
    Triangle t;
    t.p1 = Point<float>{160.0f, 350.0f, 0.0f};
    t.p2 = Point<float>{45.0f, 30.0f, 0.0f};
    t.p3 = Point<float>{380.0f, 100.0f, 0.0f};

    Triangle v;
    v.p1 = Point<float>{40.0f, 280.0f, 0.0f};
    v.p2 = Point<float>{265.0f, 30.0f, 0.0f};
    v.p3 = Point<float>{350.0f, 360.0f, 0.0f};
    */
    device.setBackgroundColor(0.3f, 0.58f, 0.80f);

    while(!device.shouldShutdown()) {
        RasterlizeTriangle(device, t, mixed);
        RasterlizeTriangle(device, v, blue);
        //RasterlizeLine(device, 40, 80, 350, 240, 0.45f, black);

        device.refreshBuffer();
    }

    return 0;
}