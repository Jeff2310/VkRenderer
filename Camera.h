//
// Created by jeff2310 on 3/28/18.
//

#ifndef VKSOFTWARERENDER_CAMERA_H
#define VKSOFTWARERENDER_CAMERA_H

#include "MathUtility.h"

namespace VkRenderer {
    class Camera {
    private:
        Vector _cameraPos;
        float _pitch, _yaw;
        Matrix _viewMatrix;
        Vector _direction;
    public:
        Camera(float x, float y, float z);

        explicit Camera(const Vector &pos);

        void updateView(float delta_pitch, float delta_yaw);

        void updatePos(const Vector &delta_r);

        void updatePos(float delta_x, float delta_y, float delta_z);

        Vector pos();

        Matrix viewMatrix();
    };
}
#endif //GRAPHICS_CAMERA_H
