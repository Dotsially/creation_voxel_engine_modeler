#pragma once
#include "depedencies.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class NodeItem{
private:   
    glm::vec3 position = glm::vec3{0};
    glm::vec3 rotation = glm::vec3{0};
    glm::vec3 size = glm::vec3{1};
    glm::vec3 pivot = glm::vec3{0};
    glm::mat4 transform;
    NodeItem* parent = NULL;

public:
    void Initialize(NodeItem* parent, u8 isBone);
    void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 pivot);
    void CenterPivot();
    glm::vec3 GetPosition();
    glm::vec3 GetPivot();
    glm::vec3 GetSize();    
    glm::vec3 GetRotation();
    glm::mat4 GetTransform();
    
    u8 isBone = 0;
};