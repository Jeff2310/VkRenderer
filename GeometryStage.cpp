//
// Created by jeff2310 on 4/19/18.
//

#include "MathUtility.h"
#include "Rasterisation.h"
#include "PhongShading.h"

namespace VkRenderer {

    void homogenize(Vector *v) {
        float inv = 1.0f / v->w;
        // 透视除法并将坐标转换至屏幕空间
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
        v->w = inv; // 保存1/z, 用于顶点属性（除z之外会受透视影响的属性、纹理坐标、颜色等）的透视矫正插值
    }

    void toViewport(VirtualDevice &device, Vector *v) {
        v->x = (v->x + 1.0f) * 0.5f * device.getWidth();
        v->y = (v->y + 1.0f) * 0.5f * device.getHeight();
    }

    void RenderTriangle(VirtualDevice &device, const Triangle &t) {
        Vertex _p1 = t.p1, _p2 = t.p2, _p3 = t.p3;

        // 对每一个顶点调用shader进行处理
        PhongVertex(&_p1);
        PhongVertex(&_p2);
        PhongVertex(&_p3);

        // 将图元的坐标映射到CVV(也要更改法向量)
        homogenize(&_p1.pos);
        homogenize(&_p2.pos);
        homogenize(&_p3.pos);

        // 在CVV中裁剪
        if (_p1.pos.x > 1.0f || _p1.pos.x < -1.0f || _p2.pos.x > 1.0f || _p2.pos.x < -1.0f || _p3.pos.x > 1.0f ||
            _p3.pos.x < -1.0f)
            return;
        if (_p1.pos.y > 1.0f || _p1.pos.y < -1.0f || _p2.pos.y > 1.0f || _p2.pos.y < -1.0f || _p3.pos.y > 1.0f ||
            _p3.pos.y < -1.0f)
            return;
        if (_p1.pos.z > 1.0f || _p1.pos.z < 0.0f || _p2.pos.z > 1.0f || _p2.pos.z < 0.0f || _p3.pos.z > 1.0f ||
            _p3.pos.z < 0.0f)
            return;

        toViewport(device, &_p1.pos);
        toViewport(device, &_p2.pos);
        toViewport(device, &_p3.pos);


        Triangle _t{_p1, _p2, _p3};

        if (device.optimizationMode & FACE_CULLING) {
            Vector faceNormal[3], facePos[3];
            faceNormal[0] = _p1.normal;
            faceNormal[1] = _p2.normal;
            faceNormal[2] = _p3.normal;
            facePos[0] = _p1.shaderVariables.fragPos;
            facePos[1] = _p2.shaderVariables.fragPos;
            facePos[2] = _p3.shaderVariables.fragPos;
            bool is_back = true;
            for (int i = 0; i < 3; i++) {
                if (faceNormal[i].dot(facePos[i] - device.camera->pos()) < 0) {
                    is_back = false;
                    break;
                }
            }
            if (is_back) return;
        }

        if (device.drawMode & DRAW_FACES) {
            RasterizeTriangle(device, _t);
        }
        if (device.drawMode & DRAW_BORDERS) {
            RasterizeLine(device, (int) _p1.pos.x, (int) _p1.pos.y, (int) _p2.pos.x, (int) _p2.pos.y, 0.01f,
                          Color(0.0f, 0.0f, 0.0f, 1.0f));
            RasterizeLine(device, (int) _p2.pos.x, (int) _p2.pos.y, (int) _p3.pos.x, (int) _p3.pos.y, 0.01f,
                          Color(0.0f, 0.0f, 0.0f, 1.0f));
            RasterizeLine(device, (int) _p1.pos.x, (int) _p1.pos.y, (int) _p3.pos.x, (int) _p3.pos.y, 0.01f,
                          Color(0.0f, 0.0f, 0.0f, 1.0f));
        }
    }

    void Mesh::render(VirtualDevice &device) {
        for (int i = 0; i < faces.size(); i++) {
            RenderTriangle(device, faces[i]);
        }
    }
}
