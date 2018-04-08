using namespace std;
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Shader.h"
#include "Drawable.h"
#include "Triangle.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 1000, HEIGHT = 700;

//implementacao das classes

class Face {
	int verts[6];
	int norms[6];
	int texts[6];
public:
	Face(int verts[], int norms[], int texts[]);
};

Face::Face(int verts[], int norms[], int texts[]) {
	verts = verts;
	norms = norms;
	texts = texts;
};

class Group {
	char* name;
	char* material;
	vector<Face*> faces;

public:
	void addFace(Face* face) {
		faces.push_back(face);
	}

	void setName(char* n) {
		name = n;
	}

	void setMaterial(char* m) {
		material = m;
	}

public:
	Group(char *name, char *material) {
		name = name;
		material = material;
	}	
};

class Mesh {	
	vector<Group*> groups;
	vector<glm::vec2*> mappings;
	vector<glm::vec3*> vertexes;
	vector<glm::vec3*> normals;

public:
	void addGroup(Group* group) {
		groups.push_back(group);
	}

	void addMapping(glm::vec2* mapping) {
		mappings.push_back(mapping);
	}

	void addVertex(glm::vec3* vertex) {
		vertexes.push_back(vertex);
	}
	void addNormal(glm::vec3* normal) {
		normals.push_back(normal);
	}

	vector<Group*> getGroup() {
		return groups;
	}

	vector<glm::vec2*> getMapping() {
		return mappings;
	}

	vector<glm::vec3*> getVertex() {
		return vertexes;
	}
	vector<glm::vec3*> getNormal() {
		return normals;
	}

	/*
	void setGroup(Group* group) {
		groups.push_back(group);
	}

	void setMapping(glm::vec2* mapping) {
		mappings.push_back(mapping);
	}

	void setVertex(glm::vec3* vertex) {
		vertexes.push_back(vertex);
	}
	void setNormal(glm::vec3* normal) {
		normals.push_back(normal);
	}*/
};

//leitura de OBJ
Mesh *read(string filename) {
	Mesh *mesh = new Mesh;
	ifstream arq(filename);
	while (!arq.eof()) {
		string line;
		getline(arq, line);
		stringstream sline;
		sline << line;
		string temp;
		sline >> temp;
		if (temp == "v") {
			// ler vértice ...
			float x, y, z;
			sline >> x >> y >> z;
			// ... atribuir vértices da malha
			glm::vec3 vert = glm::vec3(x, y, z);
			mesh->addVertex(&vert);
			// ...
		}
		else if (temp == "f") {
			// implementar lógica de variações
			// para face: v, v/t/n, v/t e v//n
			string token;
			sline >> token; // v/t/n, por exemplo
			stringstream stoken;
			string aux;
			getline(stoken, aux, '/');
			//guardar o indice do vertice
			int v;
			v = stoi(aux);
			//verificar qual a proxima sequencia
			if (stoken.peek() == '/') {
				stoken.get();
			}
			
			// ...
		}
		else if (temp == "vt") {
			//criar textura
			float u, v;
			sline >> u >> v;
			glm::vec2 texture = glm::vec2(u, v);
			mesh->addMapping(&texture);
		}
		else if (temp == "vn") {
			//criar normais
			float x, y, z;
			sline >> x >> y >> z;
			glm::vec3 normal = glm::vec3(x, y, z);
			mesh->addNormal(&normal);
		}
		else {// else-if
			  // Verificar outras possibilidades:
			  // g, vn, ...
			
		}
	}
	return mesh;
}


int main() {

	// Inicializando bibliotecas
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Cube from OBJ", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);


	// vbo
	GLfloat points[] = {
		0.15f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	// vbo second triangle
	GLfloat points_2[] = {
		0.15f, 0.5f, -0.5f,
		0.7f, 0.0f, -1.0f,
		0.5f, -0.5f, 0.0f
	};

	GLuint pointsVBO = 0;
	glGenBuffers(1, &pointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//vbo_2
	GLuint pointsVBO_2 = 0;
	glGenBuffers(1, &pointsVBO_2);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points_2), points_2, GL_STATIC_DRAW);

	
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat colors_line[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	GLuint colorsVBO = 0;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//vbo para inverter cores do triangle
	GLfloat colors_2[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint colorsVBO_2 = 0;
	glGenBuffers(1, &colorsVBO_2);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors_2), colors_2, GL_STATIC_DRAW);


	GLuint colorsVBO_line = 1;
	glGenBuffers(1, &colorsVBO_line);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors_line), colors_line, GL_STATIC_DRAW);



	// VAO
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	GLuint vao_line = 1;
	glGenVertexArrays(1, &vao_line);
	glBindVertexArray(vao_line);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO_line);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	//second triangle
	// VAO
	GLuint vao_2 = 2;
	glGenVertexArrays(1, &vao_2);
	glBindVertexArray(vao_2);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO_2);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO_2);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	GLuint vao_line_2 = 3;
	glGenVertexArrays(1, &vao_line_2);
	glBindVertexArray(vao_line_2);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO_2);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO_line);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Shaders
	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"out vec3 color;"
		"void main () {"
		"color = vc;"
		"gl_Position = vec4(vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main() {"
		"fragColor = vec4(color, 1.0);"
		"}";


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs_t = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_t, 1, &fragment_shader, NULL);
	glCompileShader(fs_t);


	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs_t);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);


	// main loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(shader_programme);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glBindVertexArray(vao_line);
		glLineWidth(5.f);
		glDrawArrays(GL_LINE_LOOP, 0, 3);

		//second triangle
		glBindVertexArray(vao_2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//second line
		glBindVertexArray(vao_line_2);
		glDrawArrays(GL_LINE_LOOP, 0, 3);


		glfwPollEvents();
		glfwSwapBuffers(window);
	}
		glfwTerminate();
		return 0;
	
}