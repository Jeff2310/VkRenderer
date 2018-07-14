//
// Created by jeff2310 on 4/25/18.
//

#ifndef VKSOFTWARERENDER_SHADERVARIABLES_H
#define VKSOFTWARERENDER_SHADERVARIABLES_H

namespace VkRenderer {

    class PhongConstants {
    public:
        const float ambient;
        const float diffuse;
        const float specular;
        int shiniess;

        Vector lightPos;
        const Color lightColor;

        PhongConstants() : ambient(1.0f), diffuse(1.0f), specular(1.0f), shiniess(16), lightPos(),
                           lightColor() {}

        PhongConstants(float _ambient, float _diffuse, float _specular, int _shiniess, const Vector &_lightPos,
                       const Color &_lightColor) : ambient(_ambient), diffuse(_diffuse),
                                                   specular(_specular), shiniess(_shiniess),
                                                   lightPos(_lightPos),
                                                   lightColor(_lightColor) {}
    };

    class PhongVariables {
    public:
        Vector fragPos;

        PhongVariables() : fragPos(0.0f, 0.0f, 0.0f) {}

        PhongVariables(Vector _pos) : fragPos(_pos) {}

        static PhongVariables
        variablesInterp(const PhongVariables &v1, const PhongVariables &v2, float world_t) {
            PhongVariables v;
            v.fragPos = interp(v1.fragPos, v2.fragPos, world_t);
            return v;
        }
    };

    extern PhongConstants normalPhongConstants;
}

#endif //VKSOFTWARERENDER_SHADERVARIABLES_H
