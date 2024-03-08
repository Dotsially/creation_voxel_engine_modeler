#pragma once
#include "depedencies.h"
#include "vertices_list.h"
#include "mesh.h"


class Cube{
private:   
    std::vector<f32> vertices;
    std::vector<u32> indices;
    glm::mat4 transform;
    Mesh mesh;
public:
    Cube(glm::vec3 position);
    void Draw();
};