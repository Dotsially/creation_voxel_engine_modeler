#pragma once
#include "depedencies.h"
#include "node.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <map>

class SekaiReader{ 



public:
    void SaveModel(std::map<std::string, NodeItem>* items);
    void LoadModel(Node* node, std::string fileName);
};