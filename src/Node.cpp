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
            nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            if(i->first == nodeSelected){
                nodeFlags |= ImGuiTreeNodeFlags_Selected;
            }
                if(i->second.isBone){
                    u8 bone_open = ImGui::TreeNodeEx((void*)(int*)count, nodeFlags, i->first.c_str());
                    if(ImGui::IsItemClicked()){
                        nodeSelected = i->first;
                        *position = glm::vec3{0};
                        *size = glm::vec3{0};
                        *rotation = items[nodeSelected].GetRotation();
                        *pivot = items[nodeSelected].GetPivot();
                    }
                    if(ImGui::BeginDragDropSource()){
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        std::string dragText = "Node being dragged: " + nodeSelected;
                        ImGui::Text(dragText.c_str());
                        ImGui::EndDragDropSource();
                    }
                    if(bone_open){   
                        ImGui::TreePop();
                    }
                }else{
                    nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                    ImGui::TreeNodeEx((void*)(int*)count, nodeFlags, i->first.c_str());
                    if(ImGui::IsItemClicked()){
                        nodeSelected = i->first;
                        *position = items[nodeSelected].GetPosition();
                        *rotation = items[nodeSelected].GetRotation();
                        *size = items[nodeSelected].GetSize();
                        *pivot = items[nodeSelected].GetPivot();
                    }
                    if(ImGui::BeginDragDropSource()){
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        std::string dragText = "Node being dragged: " + nodeSelected;
                        ImGui::Text(dragText.c_str());
                        ImGui::EndDragDropSource();
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
    items[boneIndex].Initialize(1);
    boneSize++;
}

void Node::CenterCube(glm::vec3* pivot){
    if(!items[nodeSelected].isBone){
        items[nodeSelected].CenterPivot();
        *pivot = items[nodeSelected].GetPivot();
    }
}

void Node::AddCube(){
    std::string cubeIndex = "Cube " + std::to_string(cubeSize);
    while(items.count(cubeIndex)){
        cubeSize++;
        cubeIndex = "Cube " + std::to_string(cubeSize);
    }
    items[cubeIndex].Initialize(0);
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