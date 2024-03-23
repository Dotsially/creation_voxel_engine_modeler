#pragma once
#include "depedencies.h"
#include "vertices_list.h"
#include "mesh.h"
#include "node_item.h"
#include <vector>
#include <map>
#include <string>

typedef struct CustomBlockModelData{
    glm::vec3 size;
    glm::mat4 transform;
} CustomBlockModelData;

typedef struct EntityModelData{
    glm::vec3 size;
    glm::mat4 transform;
    BaseVertexData meshData;
} EntityModelData;

//TODO
class CustomBlockModel{
    std::vector<f32> vertices;
    std::vector<u32> indices;
    std::map<std::string, CustomBlockModelData> modelData;

    Mesh mesh;
    u8 intialized;
    
    void Generate();
public:
    void AddMesh(glm::vec3 size);
    void InitializeMesh();
    void DestroyMesh();
    void Update(glm::vec3 size);
    void Draw(glm::mat4);
};

class EntityModel{
    std::vector<f32> vertices;
    std::vector<u32> indices;
    std::map<std::string, EntityModelData> modelData;
    Mesh mesh;
    u8 intialized = 0;
    u32 meshCount = 0;
    
    void Generate();
public:
    void AddMesh(std::string meshID, NodeItem* meshData);
    void DeleteMesh(std::string meshID);
    void InitializeMesh();
    void DestroyModel();
    void Update(std::string meshID, NodeItem* meshData);
    void Clear();
    void Draw();
};