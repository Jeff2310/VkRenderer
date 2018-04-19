//
// Created by jeff2310 on 4/19/18.
//

#ifndef VKSOFTWARERENDER_PRIMITIVES_H
#define VKSOFTWARERENDER_PRIMITIVES_H

namespace VkRenderer {

    struct Color{
        float r,g,b,w;
    };

    struct TextureCoordinate{
        float u,v;
    };

    // primitives

    struct Vertex {
        Vector pos;
        TextureCoordinate texCoord;
        Color color;
        Vector normal;
    };

    struct Line {
        // 注意, Line的p1在下 p2在上
        Vertex p1, p2;
        Line():p1(),p2(){}
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

}
#endif //VKSOFTWARERENDER_PRIMITIVES_H
