//
// Created by jeff2310 on 4/19/18.
//

#include "GeometryStage.h"
#include "Rasterisation.h"

namespace VkRenderer {

    Transform Transform::currentTransform = Transform();

    Transform::Transform() {
        _model = _view = _projection = _summary = identityMatrix();
    }

    Transform::Transform(const Matrix &model, const Matrix &view, const Matrix &projection) {
        _model = model;
        _view = view;
        _projection = projection;
        _summary = _projection * _view * _model;
    }

    void Transform::setModel(const Matrix &model) {
        _model = model;
        _summary = _projection * _view * _model;
    }

    void Transform::setView(const Matrix &view) {
        _view = view;
        _summary = _projection * _view * _model;
    }

    void Transform::setProjection(const Matrix &projection) {
        _projection = projection;
        _summary = _projection * _view * _model;
    }

    Matrix Transform::getModel() {
        return _model;
    }

    Vector Transform::applyTransform(const Vector &v) {
        return _summary * v;
    }

    void bindTransform(const Transform &t) {
        Transform::currentTransform = t;
    }

    Vector homogenize(VirtualDevice &device, const Vector &v) {
        Vector _v;
        float inv = 1.0f / v.w;
        // 透视除法并将坐标转换至屏幕空间
        _v.x = v.x * inv;
        _v.y = v.y * inv;
        _v.z = v.z * inv;
        _v.w = 1.0f;
        return _v;
    }

    Vector toViewport(VirtualDevice &device, const Vector &v) {
        Vector _v = v;
        _v.x = (v.x + 1.0f) * 0.5f * device.getWidth();
        _v.y = (v.y + 1.0f) * 0.5f * device.getHeight();
        return _v;
    }

    void RenderTriangle(VirtualDevice &device, const Triangle &t) {
        Vertex _p1 = t.p1, _p2 = t.p2, _p3 = t.p3;
        Matrix _model = Transform::currentTransform.getModel();
        // mat3(transpose(inverse(model)))
        Matrix _normalTransform = _model.transpose() * _model.inverse();
        _normalTransform.value[3][0] = _normalTransform.value[3][1] = _normalTransform.value[3][2] = 0.0f;
        _normalTransform.value[3][3] = 1.0f;

        // 将图元的坐标映射到CVV(也要更改法向量)
        _p1.pos = Transform::currentTransform.applyTransform(t.p1.pos);
        _p2.pos = Transform::currentTransform.applyTransform(t.p2.pos);
        _p3.pos = Transform::currentTransform.applyTransform(t.p3.pos);
        _p1.pos = homogenize(device, _p1.pos);
        _p2.pos = homogenize(device, _p2.pos);
        _p3.pos = homogenize(device, _p3.pos);
        _p1.normal = _normalTransform * t.p1.normal;
        _p2.normal = _normalTransform * t.p2.normal;
        _p3.normal = _normalTransform * t.p3.normal;

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


        _p1.pos = toViewport(device, _p1.pos);
        _p2.pos = toViewport(device, _p2.pos);
        _p3.pos = toViewport(device, _p3.pos);


        Triangle _t{_p1, _p2, _p3};
        RasterizeTriangle(device, _t);
        RasterizeLine(device, (int) _p1.pos.x, (int) _p1.pos.y, (int) _p2.pos.x, (int) _p2.pos.y, 0.01f,
                      device.getColor(0.0f, 0.0f, 0.0f, 1.0f));
        RasterizeLine(device, (int) _p2.pos.x, (int) _p2.pos.y, (int) _p3.pos.x, (int) _p3.pos.y, 0.01f,
                      device.getColor(0.0f, 0.0f, 0.0f, 1.0f));
        RasterizeLine(device, (int) _p1.pos.x, (int) _p1.pos.y, (int) _p3.pos.x, (int) _p3.pos.y, 0.01f,
                      device.getColor(0.0f, 0.0f, 0.0f, 1.0f));
    }
}
