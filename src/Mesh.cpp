#include "mesh.h"
#include <iostream>

Mesh::Mesh(){

}

Mesh::~Mesh(){

}

void Mesh::DestroyMesh(){
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::InitializeMesh(i32 drawType, f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize){
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboInstanced);
    
    this->drawType = drawType;
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, verticesDataSize*sizeof(f32), verticesData, drawType);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSize*sizeof(u32), indicesData, drawType);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::AddAttribute(i32 dataSize, i32 stride, i32 offset){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glVertexAttribPointer(attributeCount, dataSize, GL_FLOAT, GL_FALSE, stride*sizeof(f32), (void*)(offset*sizeof(f32)));
    glEnableVertexAttribArray(attributeCount);
    attributeCount++;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::SendData(f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, verticesDataSize*sizeof(f32), verticesData, drawType);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSize*sizeof(u32), indicesData, drawType);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::AddInstanceData(i32 drawType, f32* verticesData, i32 verticesDataSize){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vboInstanced);
    glBufferData(GL_ARRAY_BUFFER, verticesDataSize*sizeof(f32), verticesData, drawType);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Mesh::AddInstanceAttribute(i32 dataSize, i32 stride, i32 offset){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vboInstanced);

    glVertexAttribPointer(attributeCount, dataSize, GL_FLOAT, GL_FALSE, stride*sizeof(f32), (void*)(offset*sizeof(f32)));
    glEnableVertexAttribArray(attributeCount);
    glVertexAttribDivisor(attributeCount, 1);
    attributeCount++;
    

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::SendInstanceData(i32 drawType, f32* verticesData, i32 verticesDataSize){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vboInstanced);
    glBufferData(GL_ARRAY_BUFFER, verticesDataSize*sizeof(f32), verticesData, drawType);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
}

void Mesh::DrawMesh(i32 mode, i32 indicesSize){
    glBindVertexArray(vao);
    glDrawElements(mode, indicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void Mesh::DrawInstancedMesh(i32 indicesSize, i32 instances){
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0, instances);
    glBindVertexArray(0);
}