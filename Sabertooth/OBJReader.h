#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Mesh.h"
#include <map>
using namespace std;

class Reader {
private:
	static string readRestOfLine(stringstream& line);
	static bool strContains(stringstream& line, string part);
public:
	Reader() {};
	~Reader() {};
	static Mesh* readFile(Mesh *newMesh, string filename);
};