//
// Created by jeff2310 on 4/15/18.
//

#include "MathUtility.h"

namespace VkRenderer {

    Matrix Matrix::inverse() {

        float det =  ( value[0][0] * ( value[1][1] * value[2][2] - value[1][2] * value[2][1] ) -
                        value[0][1] * ( value[1][0] * value[2][2] - value[1][2] * value[2][0] ) +
                        value[0][2] * ( value[1][0] * value[2][1] - value[1][1] * value[2][0] ) );

        // 先判断行列式是否为0。

        float det_inv  = 1.0f / det;
        Matrix _m;

        _m.value[0][0] =  det_inv * ( value[1][1] * value[2][2] - value[1][2] * value[2][1] );
        _m.value[0][1] = -det_inv * ( value[0][1] * value[2][2] - value[0][2] * value[2][1] );
        _m.value[0][2] =  det_inv * ( value[0][1] * value[1][2] - value[0][2] * value[1][1] );
        _m.value[0][3] = 0.0;

        _m.value[1][0] = -det_inv * ( value[1][0] * value[2][2] - value[1][2] * value[2][0] );
        _m.value[1][1] =  det_inv * ( value[0][0] * value[2][2] - value[0][2] * value[2][0] );
        _m.value[1][2] = -det_inv * ( value[0][0] * value[1][2] - value[0][2] * value[1][0] );
        _m.value[1][3] = 0.0;

        _m.value[2][0] =  det_inv * ( value[1][0] * value[2][1] - value[1][1] * value[2][0] );
        _m.value[2][1] = -det_inv * ( value[0][0] * value[2][1] - value[0][1] * value[2][0] );
        _m.value[2][2] =  det_inv * ( value[0][0] * value[1][1] - value[0][1] * value[1][0] );
        _m.value[2][3] = 0.0;

        _m.value[3][0] = -( value[3][0] * _m.value[0][0] + value[3][1] * _m.value[1][0] + value[3][2] * _m.value[2][0] );
        _m.value[3][1] = -( value[3][0] * _m.value[0][1] + value[3][1] * _m.value[1][1] + value[3][2] * _m.value[2][1] );
        _m.value[3][2] = -( value[3][0] * _m.value[0][2] + value[3][1] * _m.value[1][2] + value[3][2] * _m.value[2][2] );
        _m.value[3][3] = 1.0;

        return _m;
    }

    Matrix Matrix::transpose() {
        Matrix _m = *this;
        _m.value[0][1] = value[1][0];
        _m.value[0][2] = value[2][0];
        _m.value[0][3] = value[3][0];
        _m.value[1][0] = value[0][1];
        _m.value[1][2] = value[2][1];
        _m.value[1][3] = value[3][1];
        _m.value[2][0] = value[0][2];
        _m.value[2][1] = value[1][2];
        _m.value[2][3] = value[3][2];
        _m.value[3][0] = value[0][3];
        _m.value[3][1] = value[1][3];
        _m.value[3][2] = value[2][3];
        return _m;
    }

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

    Matrix translate(const Vector& pos){
        Matrix _m = identityMatrix();
        _m.value[3][0] = pos.x;
        _m.value[3][1] = pos.y;
        _m.value[3][2] = pos.z;
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

    Matrix rotate(float angle, const Vector& v){
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

    Matrix getView(const Vector& eyePos, const Vector& direction){
        Vector up{0.0f, 1.0f, 0.0f, 1.0f};
        return getView(eyePos, direction, up);
    }

    Matrix getView(const Vector& eyePos, const Vector& direction, const Vector& up){
        Matrix _m;
        Vector _front = direction.normalize() * -1.0f;
        Vector _up = up.normalize();
        Vector _right = _up.cross(_front);
        _m.value[0][0] = _right.x;
        _m.value[1][0] = _right.y;
        _m.value[2][0] = _right.z;
        _m.value[3][0] = eyePos.dot(_right) * -1.0f;
        _m.value[0][1] = _up.x;
        _m.value[1][1] = _up.y;
        _m.value[2][1] = _up.z;
        _m.value[3][1] = eyePos.dot(_up) * -1.0f;
        _m.value[0][2] = _front.x;
        _m.value[1][2] = _front.y;
        _m.value[2][2] = _front.z;
        _m.value[3][2] = eyePos.dot(_front) * -1.0f;
        _m.value[3][3] = 1.0f;
        return _m;
    }

    Matrix lookAt(const Vector& eyePos, const Vector& lookPos){
        return getView(eyePos, lookPos-eyePos);
    }

    Matrix lookAt(const Vector& eyePos, const Vector& lookPos, const Vector& up){
        return getView(eyePos, lookPos-eyePos, up);
    }

    Matrix getPerspective(float fov, float near, float far){

    }
}