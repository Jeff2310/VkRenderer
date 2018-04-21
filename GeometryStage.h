//
// Created by jeff2310 on 4/19/18.
//

#ifndef VKSOFTWARERENDER_GEOMETRYSTAGE_H
#define VKSOFTWARERENDER_GEOMETRYSTAGE_H

#include "MathUtility.h"
#include "VirtualDevice.h"
#include "Primitives.h"

namespace VkRenderer {

    class Transform {
    private:
        Matrix _model;
        Matrix _view;
        Matrix _projection;
        Matrix _summary;
    public:
        Transform static currentTransform;

        Transform();

        Transform(const Matrix &model, const Matrix &view, const Matrix &projection);

        void setModel(const Matrix &model);

        void setView(const Matrix &view);

        void setProjection(const Matrix &projection);

        Matrix getModel();

        Vector applyTransform(const Vector &v);

    };

    void bindTransform(const Transform &t);

    Vector homogenize(VirtualDevice &device, const Vector &v);

    void RenderTriangle(VirtualDevice &device, const Triangle &t);
}

#endif //VKSOFTWARERENDER_GEOMETRYSTAGE_H
