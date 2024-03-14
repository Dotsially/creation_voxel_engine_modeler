#pragma once
#include "depedencies.h"
#include "bone.h"
#include "cube.h"
#include <map>
#include <string>

class Model{
    std::map<std::string, Bone> bones;
    std::map<std::string, Cube> cubes;
public:

    void AddBone();
    void AddCube();
    void DrawCubes();
};