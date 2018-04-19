//
// Created by jeff2310 on 4/16/18.
//

#include "MathUtility.h"
#include "Rasterisation.h"
#include "VirtualDevice.h"

namespace VkRenderer{

    Vertex interp(const Vertex& v1, const Vertex& v2, float t){
        Vertex _v;
        _v.pos = interp(v1.pos, v2.pos, t);
        _v.texCoord.u = interp(v1.texCoord.u, v2.texCoord.u, t);
        _v.texCoord.v = interp(v1.texCoord.v, v2.texCoord.v, t);
        _v.color.r = interp(v1.color.r, v2.color.r, t);
        _v.color.g = interp(v1.color.g, v2.color.g, t);
        _v.color.b = interp(v1.color.b, v2.color.b, t);
        _v.color.w = interp(v1.color.w, v2.color.w, t);
        _v.normal = interp(v1.normal, v2.normal, t);
        return _v;
    }

    int DivideTriangle(SubTriangle *result, Triangle t){
        Point<float> *p1=&t.p1, *p2=&t.p2, *p3=&t.p3;
        Point<float> *p;
        // p1 p2 p3按y从小到大排列
        if(p1->y > p2->y) p = p1, p1 = p2, p2 = p;
        if(p1->y > p3->y) p = p1, p1 = p3, p3 = p;
        if(p2->y > p3->y) p = p2, p2 = p3, p3 = p;
        // 退化成直线
        if(p1->y == p2->y && p1->y == p3->y) return 0;
        if(p1->x == p2->x && p1->x == p3->x) return 0;
        // 平底三角形

        Point<float> _p1, _p2, _p3;
        
        if(p1->y == p2->y){
            if(p1->x > p2->x){
                p = p1, p1 = p2, p2 = p;
            }
            _p1=*p1 , _p2=*p2, _p3=*p3;
            result[0].bottom = p1->y;
            result[0].top = p3->y;
            result[0].left = Line(_p1, _p3);
            result[0].right = Line(_p2, _p3);
            return 1;
        }else if(p2->y == p3->y){
            if(p2->x > p3->x){
                p = p2, p2 = p3, p3 = p;
            }
            _p1=*p1 , _p2=*p2, _p3=*p3;
            result[0].bottom = p1->y;
            result[0].top = p3->y;
            result[0].left = Line(_p1, _p2);
            result[0].right = Line(_p1, _p3);
            return 1;
        }else{ //普通三角形
            _p1=*p1 , _p2=*p2, _p3=*p3;
            result[0].bottom = p1->y;
            result[0].top = result[1].bottom = p2->y;
            result[1].top = p3->y;
            //插值获得p2在线段p1p3上的投影点
            float k = (p2->y - p1->y)/(p3->y - p1->y);
            float x = interp(p1->x, p3->x, k);
            Point<float> _p0 {x, p2->y};
            // p2在p0左侧
            if(_p2.x <= _p0.x){
                result[0].left = Line(_p1, _p2);
                result[0].right = Line(_p1, _p0);
                result[1].left = Line(_p2, _p3);
                result[1].right = Line(_p0, _p3);
            }else{
                result[0].left = Line(_p1, _p0);
                result[0].right = Line(_p1, _p2);
                result[1].left = Line(_p0, _p3);
                result[1].right = Line(_p2, _p3);
            }
        }
        return 2;
    }

    Scanline generateScanline(const SubTriangle& t, int y){
        Scanline _scanline;
        _scanline.y = y;
        int left,right;
        float top, bottom, k;
        top = t.left.p2.y;
        bottom = t.left.p1.y;
        k = ((float)y-bottom)/(top-bottom);
        left = (int)lround(interp(t.left.p1.x, t.left.p2.x, k));
        top = t.right.p2.y;
        bottom = t.right.p1.y;
        k = ((float)y-bottom)/(top-bottom);
        right = (int)lround(interp(t.right.p1.x, t.right.p2.x, k));
        _scanline.left = left;
        _scanline.width = right-left;
        //_scanline.left = (int)lround(t.left.p1.x);
        //_scanline.width = (int)lround(t.right.p1.x) - _scanline.left;
        return _scanline;
    }

    void RenderScanline(VirtualDevice& device, const Scanline& scanline, float w, VkColor color){
        int screenWidth = device.getWidth();
        for(int x=scanline.left; x<=scanline.left+scanline.width; x++){
            if(x>=0 && x<screenWidth){
                // z-buffer required
                // for debug
                device.drawPixel(x, scanline.y, w, color);
            }
        }
    }

    void RenderTriangle(VirtualDevice& screen, const Triangle& t, float w, VkColor color){
        SubTriangle result[2];
        int count = DivideTriangle(result, t);
        if(count==0){

        }else{
            //cout<<count;
            for(int i=0; i<count; i++){
                for(int y=(int)lround(result[i].bottom); y<=(int)lround(result[i].top); y++){
                    if(y<0 || y>screen.getHeight()) return;
                    Scanline s = generateScanline(result[i], y);
                    RenderScanline(screen, s, w, color);
                }
            }
        }
    }

    void RenderPixel(VirtualDevice& device, int x, int y, float w, VkColor color){
        device.drawPixel(x, y, w, color);
    }

    void RenderLine(VirtualDevice& device, int x1, int y1, int x2, int y2, float w, VkColor color){
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
            device.drawPixel(x1, y1, w, color);
            return;
        } else if (x1 == x2) {
            for (y = y1; y != y2; y += (y1 < y2 ? 1 : -1)) device.drawPixel(x1, y, w, color);
            device.drawPixel(x2, y2, w, color);
            return;
        } else if (y1 == y2) {
            for (x = x1; x != x2; x += (x1 < x2 ? 1 : -1)) device.drawPixel(x, y1, w, color);
            device.drawPixel(x2, y2, w, color);
            return;
        }

        int dx = x1 > x2 ? x1 - x2 : x2 - x1;
        int dy = y1 > y2 ? y1 - y2 : y2 - y1;
        //判断直线斜率（绝对值）
        if (dx == dy) {
            for (x = x1, y = y1; x != x2; x += (x1 < x2 ? 1 : -1), y += (y1 < y2 ? 1 : -1)) device.drawPixel(x, y, w, color);
            device.drawPixel(x2, y2, w, color);
        } else if (dx > dy) {
            if (x1 > x2) {
                t = x1, x1 = x2, x2 = t;
                t = y1, y1 = y2, y2 = t;
            }
            e = -2 * dy, d = 2 * dy - dx;
            for (x = x1, y = y1; x <= x2; x++) {
                device.drawPixel(x, y, w, color);
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
                device.drawPixel(x, y, w, color);
                e += 2 * dx;
                if (e + d > 0) x += (x1 < x2 ? 1 : -1), e -= 2 * dy;
            }
        }
    }
}
