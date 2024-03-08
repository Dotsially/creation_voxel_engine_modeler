#include "grid.h"


Grid::Grid(u32 size){
    this->size = size;
    
    for(i32 i = 0; i <= size; i++){
        for(i32 j = 0; j <= size; j++){
            float x  = (float)j;
            float y  = (float)i;

            vertices.push_back(x);
            vertices.push_back(0);
            vertices.push_back(y);
        }
    }


    for(i32 i = 0; i < size; i++){
        for(i32 j = 0; j < size; j++){
            i32 row1 = i * (size+1);
            i32 row2 = (i+1) * (size+1);
            
            indices.push_back(row1 + j);
            indices.push_back(row1 + j + 1);
            indices.push_back(row1 + j + 1);
            indices.push_back(row2 + j + 1);
            
            indices.push_back(row2 + j + 1);
            indices.push_back(row2 + j);
            indices.push_back(row2 + j);
            indices.push_back(row1 + j);
        }
    }

    mesh.InitializeMesh(GL_STATIC_DRAW, vertices.data(), vertices.size(), indices.data(), indices.size());
    mesh.AddAttribute(3, 3, 0);
}

Grid::~Grid(){

}

void Grid::Draw(){
    mesh.DrawMesh(GL_LINES, indices.size());
}