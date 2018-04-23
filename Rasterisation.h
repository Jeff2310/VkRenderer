//
// Created by jeff2310 on 4/16/18.
//

#ifndef VKSOFTWARERENDER_RASTERISATION_H
#define VKSOFTWARERENDER_RASTERISATION_H

#include "MathUtility.h"
#include "VirtualDevice.h"
#include "GeometryStage.h"
#include "Primitives.h"
#include "PhongShading.h"

namespace VkRenderer {

    // 用于渲染的水平扫描线
    struct Scanline {
        Vertex lvertex, rvertex;
        int y, left, right;
    };

    // 插值得到顶点间fragment的信息
    Vertex interp(const Vertex &v1, const Vertex &v2, float t);

    // 分割三角形以供光栅化
    int DivideTriangle(SubTriangle *result, Triangle t);

    Scanline generateScanline(const SubTriangle &t, int y, int min, int max);

    void RasterizeScanline(VirtualDevice &device, const Scanline &scanline);

    void RasterizeTriangle(VirtualDevice &device, const Triangle &t);

    void RasterizePixel(VirtualDevice &device, int x, int y, float z, Color color);

    void RasterizeLine(VirtualDevice &device, int x1, int y1, int x2, int y2, float z, Color color);
}

#endif //VKSOFTWARERENDER_RASTERISATION_H
