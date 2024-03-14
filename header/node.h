#pragma once
#include "depedencies.h"
#include "imgui.h"
#include "node_item.h"
#include "cube_mesh.h"
#include <map>
#include <string>

class Node{
private:
	std::map<std::string, NodeItem> items;
	u16 boneSize = 0;
	u16 cubeSize = 0;
	
    std::map<std::string, CubeMesh> cubeMeshes;
	std::string nodeSelected = "";
public:
	Node();
	~Node();
	void SetupNodeUI(glm::vec3* position, glm::vec3* rotation, glm::vec3* size, glm::vec3* pivot);
	void AddBone();
	void AddCube();
	void DeleteNode();
	void CenterCube();
	void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 pivot);
	void Draw();
};