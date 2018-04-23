//
// Created by jeff2310 on 4/23/18.
//

#ifndef VKSOFTWARERENDER_PHONGSHADING_H
#define VKSOFTWARERENDER_PHONGSHADING_H

#include "MathUtility.h"
#include "VirtualDevice.h"

namespace VkRenderer {

    // the uniform variables
    class PhongVariables {
    public:
        const float ambient;
        const float diffuse;
        const float specular;
        int shiniess;

        Vector lightPos;
        const Color lightColor;

        PhongVariables() : ambient(1.0f), diffuse(1.0f), specular(1.0f), shiniess(32), lightPos(),
                           lightColor() {}

        PhongVariables(float _ambient, float _diffuse, float _specular, int _shiniess, const Vector &_lightPos,
                       const Color &_lightColor) : ambient(_ambient), diffuse(_diffuse),
                                                   specular(_specular), shiniess(_shiniess),
                                                   lightPos(_lightPos),
                                                   lightColor(_lightColor) {}
    };

    void PhongVertex();

    Color PhongFragment(VirtualDevice &device, const Vector &fragPos, const Vector &eyePos, const Vector &normal,
                        const Color &objectColor, PhongVariables variables);

    extern PhongVariables normalPhongVariable;
}
#endif //VKSOFTWARERENDER_PHONGSHADING_H
