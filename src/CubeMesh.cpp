#include "cube_mesh.h"


void CubeMesh::InitializeMesh(glm::vec3 size){
    this->size = size;
    
    Generate(this->size);

    mesh.InitializeMesh(GL_DYNAMIC_DRAW, vertices.data(), vertices.size(), indices.data(), indices.size());
    mesh.AddAttribute(3, 3, 0);
}

void CubeMesh::DestroyMesh(){
    mesh.DestroyMesh();
}

void CubeMesh::Generate(glm::vec3 size){
    vertices.clear();
    indices.clear();

    for(int i = 0; i < 24; i++){
        vertices.push_back(VerticesList::verticesCube[i*3] * size.x);
        vertices.push_back(VerticesList::verticesCube[i*3+1] * size.y);
        vertices.push_back(VerticesList::verticesCube[i*3+2] * size.z);
    }

    for(int j = 0; j < 6; j++){
        if(j % 2 == 0){
            for(u32 i : VerticesList::indicesCube[0]){
                indices.push_back(i + (j*4));
            }
        }
        else{
            for(u32 i : VerticesList::indicesCube[1]){
                indices.push_back(i + (j*4));
            }
        }
        
    }
}

void CubeMesh::Update(glm::vec3 size){
    glm::vec3 oldSize = this->size;
    this->size = size;
    if(oldSize != this->size){
        Generate(this->size);
    }

    mesh.SendData(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void CubeMesh::Draw(glm::mat4 transform){
    this->transform = transform;
    glUniformMatrix4fv(2, 1, false, glm::value_ptr(transform));
    mesh.DrawMesh(GL_TRIANGLES, indices.size());
}