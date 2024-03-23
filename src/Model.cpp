#include "model.h"


void EntityModel::InitializeMesh(){
    mesh.InitializeMesh(GL_DYNAMIC_DRAW, vertices.data(), vertices.size(), indices.data(), indices.size());
    mesh.AddAttribute(3, 3, 0);
}

void EntityModel::AddMesh(std::string meshID, NodeItem* meshData){
    meshCount++;
    EntityModelData data;
    data.size = meshData->GetSize();
    data.transform = meshData->GetTransform();
    modelData[meshID] = data;

    Generate();
    
    if(!this->intialized){
        InitializeMesh();
        this->intialized = 1;
    }
    else{
        mesh.SendData(vertices.data(), vertices.size(), indices.data(), indices.size());
    }
}

void EntityModel::DeleteMesh(std::string meshID){
    meshCount--;
    modelData.erase(meshID);
    Generate();
    mesh.SendData(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void EntityModel::DestroyModel(){
    mesh.DestroyMesh();
}

void EntityModel::Generate(){
    vertices.clear();
    indices.clear();

    int counter = 0;

    for (auto data = modelData.begin(); data != modelData.end(); data++){
        for(int i = 0; i < 24; i++){
            vertices.push_back(VerticesList::verticesCube[i*3] * data->second.size.x);
            vertices.push_back(VerticesList::verticesCube[i*3+1] * data->second.size.y);
            vertices.push_back(VerticesList::verticesCube[i*3+2] * data->second.size.z);
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
        data->second.meshData.count = 36;
        data->second.meshData.baseVertex = counter * 24;
        data->second.meshData.offset = sizeof(u32) * (36 * counter);

        counter++;
    }
}

void EntityModel::Update(std::string meshID, NodeItem* meshData){
    glm::vec3 oldSize = modelData[meshID].size;
    modelData[meshID].size = meshData->GetSize();
    modelData[meshID].transform = meshData->GetTransform();
    if(oldSize != modelData[meshID].size){
        Generate(); 
        mesh.SendData(vertices.data(), vertices.size(), indices.data(), indices.size());
    }
}

void EntityModel::Clear(){
    modelData.clear();
}

void EntityModel::Draw(){
    std::vector<BaseVertexData> meshData;
    std::vector<glm::mat4> transforms;
    for (auto data = modelData.begin(); data != modelData.end(); data++){
        meshData.push_back(data->second.meshData);
        transforms.push_back(data->second.transform);
    }

    glUniformMatrix4fv(2, transforms.size(), false, glm::value_ptr(transforms[0]));
    mesh.DrawMeshMultiBaseVertex(GL_TRIANGLES, meshCount, meshData.data());
}

