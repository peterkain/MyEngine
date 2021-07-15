#include "GL/Camera.h"

namespace engine {

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
    _front{ glm::vec3{0.f, 0.f, -1.f} }, _speed{ 10.f }, _sensitivity{ .1f }, _zoom{ 45.f }, _position{ pos },
    _world_up{ up }, _yaw{ yaw }, _pitch{ pitch }, _zoom_ortho_max{ 10.f }, _zoom_ortho_steps{ 10 }
{
    update();
}


void Camera::move(CameraMovement dir, float dt)
{
    float v{ _speed * dt };
    switch (dir)
    {
    case CameraMovement::Up:
        _position += _up * v; break;
    case CameraMovement::Down:
        _position -= _up * v; break;
    case CameraMovement::Right:
        _position += _right * v; break;
    case CameraMovement::Left:
        _position -= _right * v; break;
    case CameraMovement::Front:
        _position += _front * v; break;
    case CameraMovement::Back:
        _position -= _front * v; break;
    }
}


void Camera::rotate(glm::vec2 offset, bool constrain_pitch)
{
    offset *= _sensitivity;

    _yaw += offset.x;
    _pitch += offset.y;

    if (constrain_pitch)
        _pitch = glm::clamp(_pitch, -89.f, 89.f);

    update();
}


void Camera::zoom(float y_offset)
{
    _zoom = glm::clamp(_zoom - y_offset, 1.f, 70.f);
}


void Camera::zoom_ortho(float y_offset)
{
    static float min_00{ _projection[0][0] };
    static float min_11{ _projection[1][1] };
    float max_00{ min_00 * _zoom_ortho_max };
    float max_11{ min_11 * _zoom_ortho_max };
    float zoom_00{ (max_00 - min_00) / _zoom_ortho_steps };
    float zoom_11{ (max_11 - min_11) / _zoom_ortho_steps };

    _projection[0][0] = glm::clamp(_projection[0][0] + y_offset * zoom_00, min_00, max_00);
    _projection[1][1] = glm::clamp(_projection[1][1] + y_offset * zoom_11, max_11, min_11);
}


void Camera::setup(float x, float y, float w, float h, float near, float far, CameraType type, float zoom_ortho_min)
{
    _screen_size.x = x;
    _screen_size.y = y;
    _screen_size.z = w * zoom_ortho_min;
    _screen_size.w = h * zoom_ortho_min;
    _near = near;
    _far = far;

    switch (type)
    {
    case CameraType::Orthographic:
        _projection = glm::ortho(_screen_size.x - _screen_size.z, _screen_size.z, _screen_size.w,
            _screen_size.y - _screen_size.w, _near, _far);
        break;
    case CameraType::Perspective:
        _projection = glm::perspective(glm::radians(_zoom), _screen_size.z / _screen_size.w, _near, _far);
        break;
    }
}


void Camera::update()
{
    glm::vec3 dir;
    dir.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    dir.y = sin(glm::radians(_pitch));
    dir.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(dir);
    _right = glm::normalize(glm::cross(_world_up, _front));
    _up = glm::normalize(glm::cross(_front, _right));
}

}