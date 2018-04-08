#ifndef GROUP_H
#define GROUP_H

#include <GL\glew.h>

#include <string>
#include <vector>

#include "Face.h"

class Group
{

public:

	Group();
	~Group();

	void SetName(std::string name) {
		this->name = name;
	};
	void SetMaterial(std::string material) {
		this->material = material;
	};

	std::string GetName() {
		return name;
	};
	std::string GetMaterial() {
		return material;
	};

	void AddFace(std::vector<int>* vertexIndices, std::vector<int>* normalIndices, std::vector<int>* mappingIndices);
	std::vector<Face*>* GetFaces() {
		return faces;
	}

	GLint GetFacesSize() {
		return faces->size();
	}

	void Bind(std::vector<GLfloat> vertices, GLuint vbo);

	GLuint VAO() {
		return vbo;
	}
	GLuint VBO() {
		return vbo;
	}

private:

	std::string name;
	std::string material;

	std::vector<Face*>* faces;

	GLuint vao, vbo;

};

#endif