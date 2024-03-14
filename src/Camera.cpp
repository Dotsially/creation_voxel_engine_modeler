#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position){
    this->position = position;
    this->target = glm::vec3{5.0f,0.0f,5.0f};
    this->up = glm::vec3{0.0f,1.0f,0.0f};;
    this->fov = glm::radians(60.0);
    this->angle = glm::vec2(0,0);   
}

Camera::~Camera(){
    
}


void Camera::Update(const u8* keystate, glm::vec3 targetPosition){    
    int x;
    int y;
    if(SDL_GetRelativeMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
        angle.x -= x*0.01f;
        angle.y -= y*0.01f;
    }
    if (angle.y > glm::radians(89.0f))
    {
        angle.y = glm::radians(89.0f);
    }
    else if (angle.y < glm::radians(-89.0f))
    {
        angle.y = glm::radians(-89.0f);
    }
    
    position.x = - (sinf(angle.x) * 12.0 * cosf(angle.y) + target.x);
    position.y = ((angle.y <= 0.0f)? 1 : -1) * sinf(angle.y) * 12.0 * sinf(angle.y) + target.y;
    position.z =  - (cosf(angle.x) * 12.0 * cosf(angle.y) + target.z);

    target = targetPosition;
    forward = -glm::normalize(position - target);
    right = glm::normalize(glm::cross(forward, glm::vec3(0,1,0)));
    up =  glm::normalize(glm::cross(right, forward));
}    


glm::mat4 Camera::GetViewMatrix(){  
    return glm::lookAt(this->position, this->target, this->up);
}

glm::mat4 Camera::GetProjectMatrix(){
    return glm::perspective(this->fov, 1280.0f/720.0f, 0.1f, 1000.0f);
}


glm::vec3 Camera::GetPosition(){    
    return position;
}

glm::vec3 Camera::GetForward(){
    return forward;
}

glm::vec3 Camera::GetTarget(){
    return target;
}       

glm::vec3 Camera::GetRight(){
    return right;
}

glm::vec3 Camera::GetUp(){
    return up;
}

f32 Camera::GetFov(){
    return fov;
}