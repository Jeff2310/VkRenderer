//
// Created by jeff2310 on 4/15/18.
//

#ifndef VKSOFTWARERENDER_MATHUTILITY_H
#define VKSOFTWARERENDER_MATHUTILITY_H

#include <cmath>
#include <iostream>

namespace VkRenderer {

    template<typename T> struct Point{
        T x,y,z;
    };

    // 列向量
    struct Vector {
        float x, y, z, w;
        Vector(){
            this->x = this->y = this->z = 0;
            this->w = 1.0f;
        }
        Vector(float x, float y, float z = 0, float w = 1.0f) {
            this->x = x, this->y = y, this->z = z, this->w = w;
        }
        Vector(const Vector& v){
            this->x = v.x; this->y = v.y, this->z = v.z, this->w = v.w;
        }

        float length() const{
            return sqrtf(x * x + y * y + z * z);
        }

        Vector operator+(const Vector &v) const {
            Vector _v(x + v.x, y + v.y, z + v.z);
            return _v;
        }

        Vector operator-(const Vector &v) const {
            Vector _v(x + v.x, y + v.y, z + v.z);
            return _v;
        }

        Vector operator*(const float v) const {
            Vector _v(x*v, y*v, z*v);
            return _v;
        }

        Vector operator/(const float v) const {
            Vector _v(x/v, y/v, z/v);
            return _v;
        }

        Vector cross(const Vector &v) const {
            Vector _v(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
            return _v;
        }

        float dot(const Vector &v) const {
            return x * v.x + y * v.y + z * v.z;
        }
        Vector normalize() const {
            Vector _v(*this);
            return _v/length();
        }

    };

    struct Matrix {
        float value[4][4];
        Matrix(){
            for(int i=0; i<16; i++) *(value[0]+i) = 0.0f;
        }
        Matrix operator+(const Matrix& m) {
            Matrix _m;
            for(int i=0; i<16; i++) *(_m.value[0]+i) = *(value[0]+i) + *(m.value[0]+i);
            return _m;
        }
        Matrix operator-(const Matrix& m) {
            Matrix _m;
            for(int i=0; i<16; i++) *(_m.value[0]+i) = *(value[0]+i) - *(m.value[0]+i);
            return _m;
        }
        // 矩阵数乘
        Matrix operator*(const float t){
            Matrix _m;
            for(int i=0; i<16; i++) *(_m.value[0]+i) = *(value[0]+i) * t;
            return _m;
        }
        // 矩阵右乘
        Matrix operator*(const Matrix& m){
            int i, j;
            Matrix _m;
            for (i=0; i<4; i++) {
                for (j=0; j<4; j++) {
                    _m.value[i][j] = (value[i][0]* m.value[0][j])+
                                      (value[i][1]* m.value[1][j])+
                                      (value[i][2]* m.value[2][j])+
                                      (value[i][3]* m.value[3][j]);
                }
            }
            return _m;
        }
        // 向量左乘矩阵
        Vector operator*(const Vector& v){
            Vector _v;
            _v.x = v.x * value[0][0] + v.y * value[0][1] + v.z * value[0][2] + v.w * value[0][3];
            _v.y = v.x * value[1][0] + v.y * value[1][1] + v.z * value[1][2] + v.w * value[1][3];
            _v.z = v.x * value[2][0] + v.y * value[2][1] + v.z * value[2][2] + v.w * value[2][3];
            _v.w = v.x * value[3][0] + v.y * value[3][1] + v.z * value[3][2] + v.w * value[3][3];
            return _v;
        }

        Matrix inverse();

        Matrix transpose();
    };

    float interp(float x1, float x2, float t);
    Vector interp(const Vector &v1, const Vector& v2, float t);
    Matrix identityMatrix();
    Matrix translate(float x, float y, float z);
    Matrix translate(const Vector& pos);
    Matrix scale(float tx, float ty, float tz);
    Matrix rotate(float angle, const Vector& v);
    Matrix getView(const Vector& eyePos, const Vector& direction);
    Matrix getView(const Vector& eyePos, const Vector& direction, const Vector& up);
    Matrix lookAt(const Vector& eyePos, const Vector& lookPos);
    Matrix lookAt(const Vector& eyePos, const Vector& lookPos, const Vector& up);
    Matrix getPerspective(float fov, float near, float far);
}
#endif //VKSOFTWARERENDER_MATHUTILITY_H