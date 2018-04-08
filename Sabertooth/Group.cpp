#include "Group.h"

Group::Group()
{
	faces = new std::vector<Face*>();

	glGenVertexArrays(1, &vao);
}

Group::~Group() {}

void Group::AddFace(std::vector<int>* vertexIndices, std::vector<int>* normalIndices, std::vector<int>* mappingIndices)
{
	Face* newFace = new Face(vertexIndices, normalIndices, mappingIndices);
	this->faces->push_back(newFace);
}

void Group::Bind(std::vector<GLfloat> vertices, GLuint vbo)
{

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}
