#include "node.h"

Node::Node(){

}

Node::~Node(){
    model.DestroyModel();
}

void Node::SetupNodeUI(glm::vec3* position, glm::vec3* rotation, glm::vec3* size, glm::vec3* pivot){
    i32 count = 0;
    if(ImGui::TreeNode("Items")){
        for (auto i = items.begin(); i != items.end(); i++){
            ImGuiTreeNodeFlags nodeFlags = 0;
            nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            if(i->first == nodeSelected){
                nodeFlags |= ImGuiTreeNodeFlags_Selected;
            }
            if(i->second.isBone){
                ImGui::TreeNodeEx((void*)(int*)count, nodeFlags, i->first.c_str());
                if(ImGui::IsItemClicked()){
                    nodeSelected = i->first;
                    *position = glm::vec3{0};
                    *size = glm::vec3{0};
                    *rotation = items[nodeSelected].GetRotation();
                    *pivot = items[nodeSelected].GetPivot();
                }
            }else{
                ImGui::TreeNodeEx((void*)(int*)count, nodeFlags, i->first.c_str());
                if(ImGui::IsItemClicked()){
                    nodeSelected = i->first;
                    *position = items[nodeSelected].GetPosition();
                    *rotation = items[nodeSelected].GetRotation();
                    *size = items[nodeSelected].GetSize();
                    *pivot = items[nodeSelected].GetPivot();
                }
            }
            count++;
        }   	
		ImGui::TreePop();
	}
}


void Node::AddBone(){
    std::string boneIndex = "Bone " + std::to_string(boneSize);
    while(items.count(boneIndex)){
        boneSize++;
        boneIndex = "Bone " + std::to_string(boneSize);
    }
    items[boneIndex].Initialize(NULL, 1);
    boneSize++;
}

void Node::CenterCube(){
    if(!items[nodeSelected].isBone){
        items[nodeSelected].CenterPivot();
    }
}

void Node::AddCube(){
    std::string cubeIndex = "Cube " + std::to_string(cubeSize);
    while(items.count(cubeIndex)){
        cubeSize++;
        cubeIndex = "Cube " + std::to_string(cubeSize);
    }
    items[cubeIndex].Initialize(NULL, 0);
    cubeSize++;

    model.AddMesh(cubeIndex, &items[cubeIndex]);
}

void Node::AddNode(std::string nodeName, NodeItem item){
    items[nodeName] = item;
    if(items[nodeName].isBone){
        boneSize++;
    }else{
        cubeSize++;
        model.AddMesh(nodeName, &items[nodeName]);
    }
}

void Node::DeleteNode(){
    if(items.count(nodeSelected)){
        if(!items[nodeSelected].isBone){
            model.DeleteMesh(nodeSelected);
            cubeSize--;
        }else{
            boneSize--;
        }

        items.erase(nodeSelected);    
    }
    nodeSelected = "";
}

void Node::ClearNode(){
    items.clear();
    model.Clear();
    nodeSelected = "";
}

void Node::Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 pivot){
    if(items.count(nodeSelected)){
        items[nodeSelected].Update(position, rotation, size, pivot);
        if(!items[nodeSelected].isBone){
            model.Update(nodeSelected, &items[nodeSelected]);
        }
    }
}

void Node::Draw(){
    model.Draw();
}



std::map<std::string, NodeItem>* Node::GetItems(){
    return &items;
}