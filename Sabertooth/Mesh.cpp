#include "Mesh.h"



Mesh::Mesh()
{
	vertexes = new std::vector<glm::vec3*>();
	normals = new std::vector<glm::vec3*>();
	mappings = new std::vector<glm::vec2*>();
	groups = new std::vector<Group*>();
}


Mesh::~Mesh()
{
}

void Mesh::AddGroup()
{
	Group* newGroup = new Group();
	this->groups->push_back(newGroup);
}

void Mesh::AddGroup(std::string name)
{
	Group* newGroup = new Group();
	newGroup->SetName(name);
	this->groups->push_back(newGroup);
}

void Mesh::AddGroup(std::vector<int>* vertexIndices, std::vector<int>* normalIndices, std::vector<int>* mappingIndices)
{
	Group* newGroup = new Group();
	newGroup->AddFace(vertexIndices, normalIndices, mappingIndices);
	this->groups->push_back(newGroup);
}

void Mesh::AddVertex(glm::vec3 vertex)
{
	glm::vec3* newVertex = new glm::vec3(vertex);
	this->vertexes->push_back(newVertex);
}

void Mesh::AddNormal(glm::vec3 normal)
{
	glm::vec3* newNormal = new glm::vec3(normal);
	this->normals->push_back(newNormal);
}

void Mesh::AddMapping(glm::vec2 mapping)
{
	glm::vec2* newMapping = new glm::vec2(mapping);
	this->mappings->push_back(newMapping);
}

void Mesh::Bind()
{
	//glBindVertexArray(VAO);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexes.size(), &vertexes[0] , GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	//glEnableVertexAttribArray(0);
	//
	//glBindVertexArray(0);

	std::vector<GLfloat> tempVert, tempNorm, tempTex;
	std::vector<int> *tempVertInd, *tempNormInd, *tempTexInd;
	std::vector<Face*>* facesTemp;

	// Iterate through groups
	for (std::vector<Group*>::iterator groupsIt = groups->begin(); groupsIt != groups->end(); ++groupsIt) {

		facesTemp = (*groupsIt)->GetFaces();

		// Iterate through faces 
		for (std::vector<Face*>::iterator facesIt = facesTemp->begin(); facesIt != facesTemp->end(); ++facesIt) {
			tempVertInd = (*facesIt)->GetVerts();
			for (int i = 0; i < tempVertInd->size(); i++) {
				tempVert.push_back((vertexes->at((*tempVertInd)[i]))->r);
			}
		}

	}


}
