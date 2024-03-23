#include "node_item.h"


void NodeItem::Initialize(u8 isBone){
    this->isBone = isBone;

    CalculateTransform();
}

void NodeItem::Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 pivot){
    if(isBone){
        this->pivot = pivot;
        this->rotation = rotation;
    }else{
        this->position = position;
        this->rotation = rotation;
        this->size = size;
        this->pivot = pivot;
    }
    
    CalculateTransform();
}

void NodeItem::CenterPivot(){
    pivot = position + size/2.0f;
}

glm::vec3 NodeItem::GetPosition(){
    return position;
}

glm::vec3 NodeItem::GetPivot(){
    return pivot;
}

glm::vec3 NodeItem::GetSize(){
    return size;
}

glm::vec3 NodeItem::GetRotation(){
    return rotation;
}

glm::mat4 NodeItem::GetTransform(){
    return transform;
}

void NodeItem::CalculateTransform(){
    if(parent != NULL){
        transform = parent->GetTransform();
        transform = glm::translate(transform, pivot);
    }
    else{
        transform = glm::translate(glm::mat4(1.0), pivot);
    }

    transform = glm::rotate(transform, glm::radians(this->rotation.x), glm::vec3{1, 0, 0});
    transform = glm::rotate(transform, glm::radians(this->rotation.y), glm::vec3{0, 1, 0});
    transform = glm::rotate(transform, glm::radians(this->rotation.z), glm::vec3{0, 0, 1});
    transform = glm::translate(transform, this->position - this->pivot);
}   

u8 NodeItem::HasParent(){
    if(parent == NULL){
        return 0;
    }
    return 1;
}