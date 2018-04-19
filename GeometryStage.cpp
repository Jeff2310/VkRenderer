//
// Created by jeff2310 on 4/19/18.
//

#include "GeometryStage.h"
#include "MathUtility.h"
#include "Rasterisation.h"

namespace VkRenderer {

    Transform Transform::currentTransform = Transform();

    void Transform::setModel(const Matrix& model){
        _model = model;
        _summary = _projection * _view * _model;
    }

    void Transform::setView(const Matrix& view){
        _view = view;
        _summary = _projection * _view * _model;
    }

    void Transform::setProjection(const Matrix& projection){
        _projection = projection;
        _summary = _projection * _view * _model;
    }

    Matrix Transform::getModel() {
        return _model;
    }

    Vector Transform::applyTransform(const Vector& v){
        return _summary * v;
    }

    void Transform::bindTransform(const Transform& t){
        currentTransform = t;
    }

    void RenderTriangle(VirtualDevice &screen, const Triangle &t, VkColor color){
        Vertex _p1=t.p1, _p2=t.p2, _p3=t.p3;
        Matrix _model = Transform::currentTransform.getModel();
        // mat3(transpose(inverse(model)))
        Matrix _normalTransform = _model.transpose() * _model.inverse();
        _normalTransform.value[3][0] = _normalTransform.value[3][1] = _normalTransform.value[3][2] = 0.0f;
        _normalTransform.value[3][3] = 1.0f;

        // 将图元的坐标映射到屏幕空间(也要更改法向量)
        _p1.pos = Transform::currentTransform.applyTransform(t.p1.pos);
        _p2.pos = Transform::currentTransform.applyTransform(t.p2.pos);
        _p3.pos = Transform::currentTransform.applyTransform(t.p3.pos);
        _p1.normal = _normalTransform * _p1.normal;
        _p2.normal = _normalTransform * _p2.normal;
        _p3.normal = _normalTransform * _p3.normal;

        Triangle _t {_p1, _p2, _p3};
        RasterlizeTriangle(screen, _t, color);
    }
}
