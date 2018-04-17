//
// Created by jeff2310 on 4/15/18.
//

#include "MathUtility.h"

namespace VkRenderer {

    float interp(float x1, float x2, float t) {
        return x1 + (x2 - x1) * t;
    }

    Vector interp(const Vector &v1, const Vector &v2, float t) {
        Vector _v(interp(v1.x, v2.x, t),
                  interp(v1.y, v2.y, t),
                  interp(v1.z, v2.z, t));
        return _v;
    }

    Matrix identityMatrix(){
        Matrix _m;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                _m.value[i][j] = (i==j? 1.0f: 0.0f);
            }
        }
        return _m;
    }

    Matrix translate(float x, float y, float z){
        Matrix _m = identityMatrix();
        _m.value[3][0] = x;
        _m.value[3][1] = y;
        _m.value[3][2] = z;
        return _m;
    }

    Matrix scale(float tx, float ty, float tz){
        Matrix _m;
        _m.value[0][0] = tx;
        _m.value[1][1] = ty;
        _m.value[2][2] = tz;
        _m.value[3][3] = 1.0f;
        return _m;
    }

    Matrix rotate(float angle, Vector v){
        float x=v.x, y=v.y, z=v.z;
        float x2=x*x, y2=y*y, z2=z*z;
        float cos=cosf(angle), sin=sinf(angle);
        Matrix _m;
        _m.value[0][0] = x2+(1-x2)*cos;
        _m.value[0][1] = x*y*(1-cos)+z*sin;
        _m.value[0][2] = x*y*(1-cos)-y*sin;
        _m.value[1][0] = x*y*(1-cos)-z*sin;
        _m.value[1][1] = y2+(1-y2)*cos;
        _m.value[1][2] = y*z*(1-cos)+x*sin;
        _m.value[2][0] = x*z*(1-cos)+y*sin;
        _m.value[2][1] = y*z*(1-cos)-x*sin;
        _m.value[2][2] = z2+(1-z2)*cos;
        _m.value[3][3] = 1.0f;
    }
}