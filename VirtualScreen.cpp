//
// Created by jeff2310 on 4/15/18.
//

#include "VirtualScreen.h"

namespace VkRenderer {

    void VirtualScreen::DrawPixel(int x, int y, char value){
        //if(value=='@') cout<<"write to "<<x<<","<<y<<endl;
        pixels[y][x] = value;
    }

    void VirtualScreen::DrawLine(int x1, int y1, int x2, int y2, char value) {
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
            DrawPixel(x1, y1, value);
            return;
        } else if (x1 == x2) {
            for (y = y1; y != y2; y += (y1 < y2 ? 1 : -1)) DrawPixel(x1, y, value);
            DrawPixel(x2, y2, value);
            return;
        } else if (y1 == y2) {
            for (x = x1; x != x2; x += (x1 < x2 ? 1 : -1)) DrawPixel(x, y1, value);
            DrawPixel(x2, y2, value);
            return;
        }

        int dx = x1 > x2 ? x1 - x2 : x2 - x1;
        int dy = y1 > y2 ? y1 - y2 : y2 - y1;
        //判断直线斜率（绝对值）
        if (dx == dy) {
            for (x = x1, y = y1; x != x2; x += (x1 < x2 ? 1 : -1), y += (y1 < y2 ? 1 : -1)) DrawPixel(x, y, value);
            DrawPixel(x2, y2, value);
        } else if (dx > dy) {
            if (x1 > x2) {
                t = x1, x1 = x2, x2 = t;
                t = y1, y1 = y2, y2 = t;
            }
            e = -2 * dy, d = 2 * dy - dx;
            for (x = x1, y = y1; x <= x2; x++) {
                DrawPixel(x, y, value);
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
                DrawPixel(x, y, value);
                e += 2 * dx;
                if (e + d > 0) x += (x1 < x2 ? 1 : -1), e -= 2 * dy;
            }
        }
    }

}