#include <iostream>
#include "GeometryStage.h"
#include "Rasterisation.h"
#include "Camera.h"

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

    device.setBackgroundColor(0.3f, 0.58f, 0.80f);
    Transform::currentTransform.setView(
            getView(Vector(0.0f, 0.0f, 1.5f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)));
    Transform::currentTransform.setProjection(getPerspective(45.0f, 1.0f, 0.1f, 100.0f));

    device.setMode(DRAW_BORDERS, true);
    device.setMode(DRAW_FACES, false);

    while (!device.shouldShutdown()) {

        device.refreshBuffer();
        device.mainLoop();

        Transform::currentTransform.setModel(translate(normalPhongConstants.lightPos) * scale(0.2f, 0.2f, 0.2f));
        cube.render(device);

        Transform::currentTransform.setModel(translate(0.0f, 0.0f, 0.0f));
        cube.render(device);
    }

    return 0;
}