//
// Created by jeff2310 on 4/21/18.
//

#include "Camera.h"

namespace VkRenderer {
    Camera::Camera(float x, float y, float z) : _cameraPos(x, y, z) {
        _direction = Vector(0.0f, 0.0f, -1.0f);
        _viewMatrix = getView(_cameraPos, _direction);
        _pitch = _yaw = 0.0f;
    }

    Camera::Camera(const Vector &pos) {
        // right hand coordinate system
        _cameraPos = pos;
        _direction = Vector(0.0f, 0.0f, -1.0f);
        _viewMatrix = getView(_cameraPos, _direction);
        _pitch = _yaw = 0.0f;
    }

    void Camera::updateView(float delta_pitch, float delta_yaw) {

        _pitch += delta_pitch;
        _yaw += delta_yaw;

        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
        if (_yaw > 359.0f)
            _yaw -= 359.0f;
        if (_yaw < -359.0f)
            _yaw += 359.0f;

        Matrix rotation = rotate(_yaw, Vector(0.0f, 1.0f, 0.0f)) * rotate(_pitch, Vector(1.0f, 0.0f, 0.0f));
        Vector currentDirection = (rotation * _direction).normalize();
        _viewMatrix = getView(_cameraPos, currentDirection);
    }

    void Camera::updatePos(const Vector &delta_r) {
        // why is it -yaw here?
        // because when yaw angle increases while X position decreases.
        Matrix yawRotate = rotate(_yaw, Vector(0.0f, 1.0f, 0.0f));
        _cameraPos = _cameraPos + yawRotate * delta_r;
        Matrix rotation = yawRotate * rotate(_pitch, Vector(1.0f, 0.0f, 0.0f));
        Vector currentDirection = rotation * _direction;
        _viewMatrix = getView(_cameraPos, currentDirection);
    }

    void Camera::updatePos(float delta_x, float delta_y, float delta_z) {
        updatePos(Vector(delta_x, delta_y, delta_z));
    }

    Vector Camera::pos() {
        return _cameraPos;
    }

    Matrix Camera::viewMatrix() {
        return _viewMatrix;
    }
}
