#include "cube.h"


Cube::Cube(glm::vec3 position){
    transform = glm::translate(glm::mat4(1.0), glm::vec3{position.x, position.y + 0.5, position.z});

    vertices.insert(vertices.begin(), VerticesList::verticesCube[0], VerticesList::verticesCube[0]+72);

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

    mesh.InitializeMesh(GL_STATIC_DRAW, vertices.data(), vertices.size(), indices.data(), indices.size());
    mesh.AddAttribute(3, 3, 0);
}



void Cube::Draw(){
    glUniformMatrix4fv(2, 1, false, glm::value_ptr(transform));
    mesh.DrawMesh(GL_TRIANGLES, indices.size());
}