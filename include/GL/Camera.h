#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Logger.h"
#include "Event.h"


namespace engine { 
    enum class CameraType
    {
        Orthographic,
        Perspective
    };

    enum class CameraMovement
    {
        Up, Down, Left, Right, Front, Back
    };

	class Camera {
        glm::vec3 _position, _front, _up, _right, _world_up;
        float _yaw, _pitch, _speed, _sensitivity, _zoom, _zoom_ortho_max;
        u8 _zoom_ortho_steps;
        glm::mat4 _projection;
        glm::vec4 _screen_size;
        float _near, _far;
    public:
        Camera(glm::vec3 pos = glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3 up = glm::vec3{ 0.f, 1.f, 0.f }, float yaw = -90.f, float pitch = 0.f);

        inline glm::mat4 view() const { return glm::lookAt(_position, _position + _front, _up); }
        inline glm::mat4 projection() const { return _projection; }
        inline glm::vec3 position() const { return _position; }
        inline void speed(float speed) { _speed = abs(speed); }

        void move(CameraMovement dir, float dt);
        void rotate(glm::vec2 offset, bool constrain_pitch = true);
        void zoom(float y_offset);
        void zoom_ortho(float y_offset);

        inline void zoom_ortho_max(float factor) { _zoom_ortho_max = factor; }
        inline void zoom_ortho_steps(u8 steps) { _zoom_ortho_steps = steps; }

        void setup(float x, float y, float w, float h, float near, float far, CameraType type, float zoom_ortho_min = 1.f);

    private:
        void update();
	};
}