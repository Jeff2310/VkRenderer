//
// Created by jeff2310 on 4/16/18.
//

#ifndef VKSOFTWARERENDER_RASTERISATION_H
#define VKSOFTWARERENDER_RASTERISATION_H

#include "MathUtility.h"
#include "VirtualScreen.h"

namespace VkRenderer {

    struct Color{
        float r,g,b,w;
    };

    struct TextureCoordinate{
        float u,v;
    };

    // 用于渲染的水平扫描线
    struct Scanline{
        int y, left, width;
    };

    // primitives
    struct Vertex{
        Vector pos;
        TextureCoordinate texCoord;
        Color color;
        Vector normal;
    };

    struct Triangle{
        Point<float> p1, p2, p3;
    };
    // 分割用的子三角形
    struct SubTriangle{
        float top, bottom;
        Line left, right;
    };

    // 计算顶点插值
    Vertex interp(const Vertex& v1, const Vertex &v2, float t);
    // 分割三角形以供光栅化
    int DivideTriangle(SubTriangle *result,Triangle t);

    Scanline generateScanline(const SubTriangle& t, int y);

    void RenderScanline(VirtualScreen& screen, const Scanline& scanline);

    void RenderTriangle(VirtualScreen& screen, const Triangle& t);
}

#endif //VKSOFTWARERENDER_RASTERISATION_H
