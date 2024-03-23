#pragma once
#include "depedencies.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

class Camera{
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 worldUp;
    glm::vec3 right;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 moveDirection;
    glm::vec2 lastMouse;
    glm::vec2 angle;
    glm::vec2 initialAngle;
    f32 percentMoved;
    f32 fov;
    f32 yaw;
    f32 pitch;
    f32 targetDistance = 12.0f;

public:
    Camera(glm::vec3 position);
    ~Camera();
    void Update(const u8* keystate, glm::vec3 targetPosition);
    void UpdateTargetDistance(i32 y);
    glm::mat4 GetProjectMatrix();
    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition();
    glm::vec3 GetTarget();
    glm::vec3 GetRight();
    glm::vec3 GetForward();
    glm::vec3 GetUp();
    f32 GetFov();
};