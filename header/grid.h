#pragma once
#include "depedencies.h"
#include "mesh.h"
#include <vector>

class Grid{
private:
    std::vector<f32> vertices;
    std::vector<u32> indices;
    Mesh mesh;
    u32 size;

public:
    Grid(u32 size);
    ~Grid();
    void Draw();
};