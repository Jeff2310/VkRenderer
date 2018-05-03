//
// Created by jeff2310 on 4/19/18.
//

#ifndef VKSOFTWARERENDER_PRIMITIVES_H
#define VKSOFTWARERENDER_PRIMITIVES_H

#include "MathUtility.h"
#include "ShaderVariables.h"
#include "VirtualDevice.h"

#include <vector>

namespace VkRenderer {
    // primitives

    class Vertex {
    public:
        Vector pos;
        TextureCoordinate texCoord;
        Color color;
        Vector normal;
        PhongVariables shaderVariables;

        Vertex() : texCoord(), shaderVariables() {}

        Vertex(const Vector &_pos, const TextureCoordinate &_texCoord, const Color &_color,
               const Vector &_normal, const PhongVariables &_shaderVariables) :
                pos(_pos), texCoord(_texCoord),
                color(_color), normal(_normal),
                shaderVariables(_shaderVariables) {}
    };

    struct Line {
        // 注意, Line的p1在下 p2在上
        Vertex p1, p2;

        Line() : p1(), p2() {}

        Line(const Vertex &_p1, const Vertex &_p2) : p1(_p1), p2(_p2) {}
    };

    struct Triangle {
        Vertex p1, p2, p3;
    };
    // 分割用的子三角形
    struct SubTriangle {
        float top, bottom;
        Line left, right;
    };

    class Mesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<Triangle> faces;
        int vertexCount;
    public:
        Mesh();

        Mesh(const Mesh &m);

        int count();

        void addVertex(const Vertex &v);

        void build();

        void render(VirtualDevice &device);

    };

    Mesh createCube(float length, const Color *colors);

    Mesh createSphere(float radius, float angle_step);

    Vertex interp(const Vertex &v1, const Vertex &v2, float t);

}
#endif //VKSOFTWARERENDER_PRIMITIVES_H
