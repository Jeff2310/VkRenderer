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
    t.p1 = Point<float>{160.0f, 350.0f, 0.0f};
    t.p2 = Point<float>{45.0f, 30.0f, 0.0f};
    t.p3 = Point<float>{380.0f, 100.0f, 0.0f};

    Triangle v;
    v.p1 = Point<float>{40.0f, 280.0f, 0.0f};
    v.p2 = Point<float>{265.0f, 30.0f, 0.0f};
    v.p3 = Point<float>{350.0f, 360.0f, 0.0f};

    device.setBackgroundColor(0.3f, 0.58f, 0.80f);

    RenderTriangle(device, t, 0.5f, mixed);
    RenderTriangle(device, v, 0.6f, blue);

    RenderLine(device, 40, 80, 350, 240, 0.55f, black);

    device.refreshBuffer();

    system("read -n1 -r -p \"Press any key to continue...\" key");
    return 0;
}