#include <iostream>
#include <iomanip>
#include "VirtualScreen.h"
#include "MathUtility.h"
#include "Rasterisation.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace VkRenderer;

using namespace std;

int main() {
    VirtualScreen screen("test", 160, 80);

    for(int i=0; i<160; i++){
        for(int j=0; j<80; j++){
            screen.DrawPixel(i,j,' ');
        }
    }

    Triangle t;
    t.p1 = Point<float>{80.0f, 15.0f, 0.0f};
    t.p2 = Point<float>{5.0f, 8.0f, 0.0f};
    t.p3 = Point<float>{45.0f, 50.0f, 0.0f};

    Triangle t2;
    t2.p1 = Point<float>{70.0f, 55.0f, 0.0f};
    t2.p2 = Point<float>{180.0f, 55.0f, 0.0f};
    t2.p3 = Point<float>{85.0f, 70.0f, 0.0f};

    Triangle t3;
    t3.p1 = Point<float>{70.0f, 40.0f, 0.0f};
    t3.p2 = Point<float>{120.0f, 40.0f, 0.0f};
    t3.p3 = Point<float>{85.0f, 25.0f, 0.0f};


    Triangle t4;
    t4.p1 = Point<float>{75.0f, 65.0f, 0.0f};
    t4.p2 = Point<float>{5.0f, 75.0f, 0.0f};
    t4.p3 = Point<float>{45.0f, 55.0f, 0.0f};

    RenderTriangle(screen, t);
    RenderTriangle(screen, t2);
    RenderTriangle(screen, t3);
    RenderTriangle(screen, t4);

    screen.DrawLine(0,0,159,0,'-');
    screen.DrawLine(0,79,159,79,'-');
    screen.DrawLine(0,1,0,78,'|');
    screen.DrawLine(159,1,159,78,'|');

    screen.Dump("screen_test");
    return 0;
}