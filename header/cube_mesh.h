#pragma once
#include "depedencies.h"
#include "vertices_list.h"
#include "mesh.h"
#include <vector>

class CubeMesh{
    std::vector<f32> vertices;
    std::vector<u32> indices;
    Mesh mesh;
    glm::vec3 size;
    glm::mat4 transform;
    
    void Generate(glm::vec3 size);
public:
    void InitializeMesh(glm::vec3 size);
    void DestroyMesh();
    void Update(glm::vec3 size);
    void Draw(glm::mat4);
};