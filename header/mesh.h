#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

typedef struct BaseVertexData{
    u32 count;
    u32 offset;
    u32 baseVertex;
} BaseVertexData;

class Mesh{
    u32 vao;
    u32 vbo;
    u32 vboInstanced;
    u32 ebo;
    i32 drawType;
    u8 attributeCount = 0;
public:
    Mesh();
    ~Mesh();

    void InitializeMesh(i32 drawType, f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize);
    void DestroyMesh();
    void AddAttribute(i32 dataSize, i32 stride, i32 offset);
    void SendData(f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize);

    void AddInstanceData(i32 drawType, f32* verticesData, i32 verticesDataSize);
    void AddInstanceAttribute(i32 dataSize, i32 stride, i32 offset);
    void SendInstanceData(i32 drawType, f32* verticesData, i32 verticesDataSize);

    void DrawMesh(i32 mode, i32 indiceSize);
    void DrawMeshBaseVertex(i32 mode, BaseVertexData* baseVertex);
    void MultiDrawElementsIndirect(i32 mode);
    void DrawInstancedMesh(i32 indicesSize, i32 instances);
};