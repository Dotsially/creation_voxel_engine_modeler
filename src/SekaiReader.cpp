#include "sekai_reader.h"
#include <iostream>
using nlohmann::json;

void SekaiReader::SaveModel(std::map<std::string, NodeItem>* items){
    std::string modelPath = "resources/models/model.json";
    std::ofstream modelFile; 
    modelFile.open(modelPath.c_str()); 

    json model = json::object();
    json meshes = json::array();

    for (auto item = items->begin(); item != items->end(); item++){
        json itemObject = json::object();

        itemObject["name"] = item->first;

        glm::vec3 position = item->second.GetPosition();
        glm::vec3 rotation = item->second.GetRotation();
        glm::vec3 size = item->second.GetSize();
        glm::vec3 pivot = item->second.GetPivot();
        i32 isBone = item->second.isBone;

        itemObject["position"] = {position.x,position.y,position.z};
        itemObject["rotation"] = {rotation.x,rotation.y,rotation.z};
        itemObject["size"] = {size.x,size.y,size.z};
        itemObject["pivot"] = {pivot.x,pivot.y,pivot.z};
        itemObject["is_bone"] = isBone;

        meshes.insert(meshes.end(), itemObject);
    }

    model["items"] = meshes;

    modelFile << model;

    modelFile.close();
}

void SekaiReader::LoadModel(Node* node, std::string fileName){
    std::string modelPath = "resources/models/" + fileName; 
    std::ifstream modelFile(modelPath.c_str());
    json model = json::parse(modelFile);

    
    node->ClearNode();
    
    for(auto it = model["items"].begin(); it != model["items"].end(); ++it){
        json data = it.value();
        NodeItem nodeItem;
        nodeItem.Initialize(NULL, data["is_bone"]);
        
        glm::vec3 position = glm::vec3{data["position"][0], data["position"][1], data["position"][2]};
        glm::vec3 rotation = glm::vec3{data["rotation"][0], data["rotation"][1], data["rotation"][2]};
        glm::vec3 size = glm::vec3{data["size"][0], data["size"][1], data["size"][2]};
        glm::vec3 pivot = glm::vec3{data["pivot"][0], data["pivot"][1], data["pivot"][2]};
        
        nodeItem.Update(position, rotation, size, pivot);
        
        node->AddNode(data["name"], nodeItem);
    }




    modelFile.close();
}