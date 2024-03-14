#pragma once
#include "depedencies.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include <string>

typedef struct KeyFrame{
    u8 hasKeyframe = 0;
    u8 hasPosition = 0;
    u8 hasRotation = 0;
    u8 hasSize = 0;
    u8 hasPivot = 0;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size;
    glm::vec3 pivot;
} KeyFrame;


class Animator{
    KeyFrame* keyframes;
    i32 keyFramesCount = 0;
    u32 currentFrame = 0;
    u32 currentKeyframe = 0;
    u32 frameTime = 60;

public:
    Animator(u32 keyFramesCount, u32 frameTime);
    ~Animator();
    void SetupAnimatorUI();


};