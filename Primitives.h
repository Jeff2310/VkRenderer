//
// Created by jeff2310 on 4/19/18.
//

#ifndef VKSOFTWARERENDER_PRIMITIVES_H
#define VKSOFTWARERENDER_PRIMITIVES_H

namespace VkRenderer {

    struct Color{
        float r,g,b,w;

        Color() : r(0.0f), g(0.0f), b(0.0f), w(1.0f) {}

        Color(float _r, float _g, float _b, float _w = 1.0f) : r(_r), g(_g), b(_b), w(_w) {
            if (r < 0.0f) r = 0.0f;
            if (r > 1.0f) r = 1.0f;
            if (g < 0.0f) g = 0.0f;
            if (g > 1.0f) g = 1.0f;
            if (b < 0.0f) b = 0.0f;
            if (b > 1.0f) b = 1.0f;
            if (w < 0.0f) w = 0.0f;
            if (w > 1.0f) w = 1.0f;
        }

        Color operator+(const Color &c) const {
            Color _c(r + c.r, g + c.g, b + c.b, w);
            return _c;
        }

        Color operator-(const Color &c) const {
            Color _c(r - c.r, g - c.g, b - c.b, w);
            return _c;
        }

        Color operator*(const Color &c) const {
            Color _c(r * c.r, g * c.g, b * c.b, w);
            return _c;
        }

        Color operator*(float t) const {
            Color _c(r * t, g * t, b * t, w);
            return _c;
        }
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
