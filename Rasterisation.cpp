//
// Created by jeff2310 on 4/16/18.
//

#include <iostream>
#include "MathUtility.h"
#include "Rasterisation.h"
#include "PhongShading.h"


namespace VkRenderer {

    int DivideTriangle(SubTriangle *result, Triangle t) {
        Vertex *p1 = &t.p1, *p2 = &t.p2, *p3 = &t.p3;
        Vertex *p;
        // p1 p2 p3按y从小到大排列
        if (p1->pos.y > p2->pos.y) p = p1, p1 = p2, p2 = p;
        if (p1->pos.y > p3->pos.y) p = p1, p1 = p3, p3 = p;
        if (p2->pos.y > p3->pos.y) p = p2, p2 = p3, p3 = p;
        // 退化成直线
        if (p1->pos.y == p2->pos.y && p1->pos.y == p3->pos.y) return 0;
        if (p1->pos.x == p2->pos.x && p1->pos.x == p3->pos.x) return 0;


        //Vertex _p1, _p2, _p3;
        // 平底三角形
        if (p1->pos.y == p2->pos.y) {
            if (p1->pos.x > p2->pos.x) {
                p = p1, p1 = p2, p2 = p;
            }
            result[0].bottom = p1->pos.y;
            result[0].top = p3->pos.y;
            result[0].left = Line(*p1, *p3);
            result[0].right = Line(*p2, *p3);
            return 1;
        } else if (p2->pos.y == p3->pos.y) {
            if (p2->pos.x > p3->pos.x) {
                p = p2, p2 = p3, p3 = p;
            }
            result[0].bottom = p1->pos.y;
            result[0].top = p3->pos.y;
            result[0].left = Line(*p1, *p2);
            result[0].right = Line(*p1, *p3);
            return 1;
        } else { //普通三角形
            result[0].bottom = p1->pos.y;
            result[0].top = result[1].bottom = p2->pos.y;
            result[1].top = p3->pos.y;
            //插值获得p2在线段p1p3上的投影点
            float k;
            if (p3->pos.y == p1->pos.y)
                k = 0.0f;
            else
                k = (p2->pos.y - p1->pos.y) / (p3->pos.y - p1->pos.y);
            Vertex _p0 = interp(*p1, *p3, k);
            // p2在p0左侧
            if (p2->pos.x <= _p0.pos.x) {
                result[0].left = Line(*p1, *p2);
                result[0].right = Line(*p1, _p0);
                result[1].left = Line(*p2, *p3);
                result[1].right = Line(_p0, *p3);
            } else {
                result[0].left = Line(*p1, _p0);
                result[0].right = Line(*p1, *p2);
                result[1].left = Line(_p0, *p3);
                result[1].right = Line(*p2, *p3);
            }
        }
        return 2;
    }

    Scanline generateScanline(const SubTriangle &t, int y) {
        Scanline _scanline;
        float top, bottom, k;
        // top 可能等于bottom， 此时不用插值直接算就行了

        _scanline.y = y;

        top = lround(t.left.p2.pos.y);
        bottom = lround(t.left.p1.pos.y);
        if (top == bottom)
            k = 0.0f;
        else
            k = ((float) y - bottom) / (top - bottom);

        _scanline.lvertex = interp(t.left.p1, t.left.p2, k);
        _scanline.left = (int) lround(_scanline.lvertex.pos.x);

        top = lround(t.right.p2.pos.y);
        bottom = lround(t.right.p1.pos.y);
        if (top == bottom)
            k = 0.0f;
        else
            k = ((float) y - bottom) / (top - bottom);
        _scanline.rvertex = interp(t.right.p1, t.right.p2, k);
        _scanline.right = (int) lround(_scanline.rvertex.pos.x);
        return _scanline;
    }

    void RasterizeScanline(VirtualDevice &device, const Scanline &scanline) {
        int screenWidth = device.getWidth();
        int left = scanline.left, right = scanline.right;
        Vertex fragment;
        float k;
#pragma omp parallel for
        for (int x = left - 1; x <= right + 1; x++) {
            // 两边扩展一下，缓解三角形连接处接不上的问题
            if (x < 0 || x > screenWidth) continue;
            if (left == right || x < left)
                k = 0.0f;
            else if (x > right)
                k = 1.0f;
            else
                k = (float) (x - left) / (right - left);
            // 扫描线两端定点插值得到fragment
            fragment = interp(scanline.lvertex, scanline.rvertex, k);
            // fragment shading
//            Vector eyePos = Transform::currentTransform.toWorld(device.camera->pos());
            Color phongColor = PhongFragment(device, fragment, normalPhongConstants);
            RasterizePixel(device, x, scanline.y, fragment.pos.z, phongColor);
        }
    }

    void RasterizeTriangle(VirtualDevice &device, const Triangle &t) {
        SubTriangle result[2];
        int count = DivideTriangle(result, t);
        if (count == 0) {
            return;
        } else {
            for (int i = 0; i < count; i++) {
                // 1为平顶三角形， 2为平底三角形
#pragma omp parallel for
                for (auto y = (int) lround(result[i].bottom); y <= (int) lround(result[i].top); y++) {
                    if (y < 0 || y > device.getHeight()) continue;// damn it
                    Scanline s = generateScanline(result[i], y);
                    RasterizeScanline(device, s);
                }
            }
        }
    }

    void RasterizePixel(VirtualDevice &device, int x, int y, float z, Color color) {
        if (x < 0 || x >= device.getWidth() || y < 0 || y >= device.getHeight()) return;
        float *pixelDepth = device.getDepth(x, y);
        float depth = z;
        if (depth < 0.0f || depth > 1.0f || depth > *pixelDepth)
            return;
        *pixelDepth = depth;
        device.drawPixel(x, y, color);
    }

    void RasterizeLine(VirtualDevice &device, int x1, int y1, int x2, int y2, float z, Color color) {
        /* 假设dx>dy
         * m=dy/dx为斜率, e为到该画的点为止之前的积累误差
         * e+=dy/dx    --> 2*dx*e+=2*dy
         * 若e+dy/dx>0.5   --> 2*dx*e+2*dy-dx>0
         * 则y+=1, e-=1
         *
         * 作代换u=2*dx*e; D=2*dy-dx;
         * u+=2*dy
         * 若u+D>0
         * 则y+=1, u-=2*dx
         */
        int x, y, t;
        int e, d;

        if (x1 == x2 && y1 == y2) {
            RasterizePixel(device, x1, y1, z, color);
            return;
        } else if (x1 == x2) {
            for (y = y1; y != y2; y += (y1 < y2 ? 1 : -1)) RasterizePixel(device, x1, y, z, color);
            RasterizePixel(device, x2, y2, z, color);
            return;
        } else if (y1 == y2) {
            for (x = x1; x != x2; x += (x1 < x2 ? 1 : -1)) RasterizePixel(device, x, y1, z, color);
            RasterizePixel(device, x2, y2, z, color);
            return;
        }

        int dx = x1 > x2 ? x1 - x2 : x2 - x1;
        int dy = y1 > y2 ? y1 - y2 : y2 - y1;
        //判断直线斜率（绝对值）
        if (dx == dy) {
            for (x = x1, y = y1; x != x2; x += (x1 < x2 ? 1 : -1), y += (y1 < y2 ? 1 : -1))
                RasterizePixel(device, x, y, z, color);
            RasterizePixel(device, x2, y2, z, color);
        } else if (dx > dy) {
            if (x1 > x2) {
                t = x1, x1 = x2, x2 = t;
                t = y1, y1 = y2, y2 = t;
            }
            e = -2 * dy, d = 2 * dy - dx;
            for (x = x1, y = y1; x <= x2; x++) {
                RasterizePixel(device, x, y, z, color);
                e += 2 * dy;
                if (e + d > 0) y += (y1 < y2 ? 1 : -1), e -= 2 * dx;
            }
        } else {
            if (y1 > y2) {
                t = x1, x1 = x2, x2 = t;
                t = y1, y1 = y2, y2 = t;
            }
            e = -2 * dx, d = 2 * dx - dy;
            for (x = x1, y = y1; y <= y2; y++) {
                RasterizePixel(device, x, y, z, color);
                e += 2 * dx;
                if (e + d > 0) x += (x1 < x2 ? 1 : -1), e -= 2 * dy;
            }
        }
    }
}
