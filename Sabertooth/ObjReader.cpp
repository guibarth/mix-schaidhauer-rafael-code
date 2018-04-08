#include "OBJReader.h"


Mesh* Reader::readFile(Mesh* newMesh, string file) {

	ifstream _arq(file);
	if (!_arq.is_open()) {
		cout << "file not found" << endl;
		exit(0);
	}

	stringstream fileLine;
	string newLine;

	int currGroup = 0;
	//Group* firstGroup = new Group();

	//newMesh->uvs.push_back(firstGroup);
	Mesh* newMesh = new Mesh();
	Group* currentGroup = nullptr;
	//std::ifstream file;
	//file.exceptions(std::ifstream::badbit);

	

	string word;
	int index = 0;
	while (!_arq.eof()) {
		getline(_arq, newLine);

		fileLine.str("");
		fileLine.clear();

		fileLine << newLine;

		word = "";
		word.clear();
		fileLine >> word;

		int lineCounter = 1;

		if (word == "#") {
			continue;
		}
		else if (word == "usemtl") {
			//newMesh->uvs[index]->material = readRestOfLine(fileLine);
		}
		else if (word == "mtllib") {
			//newMesh->_MTLfile = readRestOfLine(fileLine);
		}
		else if (word == "g") {

			std::string name;
			fileLine >> name;
			newMesh->AddGroup(name);

			/*string gName = readRestOfLine(fileLine);
			if (newMesh->uvs[index]->name.size() == 0) {
				//newMesh->uvs[index]->name = gName;
				//newMesh->uvs[index]->clicked = false;
			}
			else {
				
				index++;
				Group* newGroup = new Group();
				newGroup->clicked = false;
				newGroup->name = gName;
				newMesh->uvs.push_back(newGroup);
				currentGroup++;
				*/
		}		
		else if (word == "v") {
			float x, y, z;
			fileLine >> x;
			fileLine >> y;
			fileLine >> z;
			newMesh->AddNormal(glm::vec3(x, y, z));
		}
		else if (word == "vn") {
			float x, y, z;
			fileLine >> x;
			fileLine >> y;
			fileLine >> z;
			newMesh->AddNormal(glm::vec3(x, y, z));
		}
		else if (word == "vt") {
			float x, y;
			fileLine >> x >> y;
			newMesh->AddMapping(glm::vec2(x, y));
		}
		else if (word == "f") {
			Face* face = new Face();
			int v = 0, t = 0, n = -1;
			char garbage;
			bool typeOne = !strContains(fileLine, "/");
			bool VandN = strContains(fileLine, "//");


			std::vector<int> *posV = new std::vector<int>;
			std::vector<int> *normV = new std::vector<int>;
			std::vector<int> *texV = new std::vector<int>;
			std::string token, valueAux;
			std::stringstream tokenStream;

			

			while (!fileLine.eof()) {
				if (typeOne) { //only vertices										
					float x, y, z;
					fileLine >> x;
					fileLine >> y;
					fileLine >> z;
					posV->push_back(x);
					posV->push_back(y);
					posV->push_back(z);
				}
				else if (VandN) { //vertices and normals type
					float v, n;
					fileLine >> v;
					fileLine >> garbage;
					fileLine >> garbage;
					fileLine >> n;
					posV->push_back(v);
					normV->push_back(n);
				}
				else { // v/t OR v/t/n 
					float v, t, n;
					fileLine >> v;
					fileLine >> garbage;
					fileLine >> t;

					posV->push_back(v);
					texV->push_back(t);

					int i = fileLine.tellg();
					if (i < fileLine.str().length() && fileLine.str()[i] != ' ') {
						fileLine >> garbage;
						fileLine >> n;
						normV->push_back(n);
					}
					/*
					face->verts.push_back(v);
					face->texture.push_back(t);
					if (n != -1)
						face->normals.push_back(n);
					*/
				}
			}
			if (currentGroup != nullptr) {
				currentGroup->AddFace(posV, normV, texV);
			}
			else {
				std::cout << "ERROR::OBJREADER::NO GROUP DEFINED FOR FACE AT LINE " << lineCounter << std::endl;
			}


			//newMesh->uvs[currentGroup]->_faces.push_back(face);
		}
		else {
			continue;
		}
		lineCounter++;
	}
	_arq.close();
	return newMesh;
}


string Reader::readRestOfLine(stringstream& line) {
	string myString;

	while (!line.eof()) {
		string temp;
		line >> temp;
		myString += temp + " ";

	}
	myString.erase(myString.length() - 1, myString.length()); //remove last space

	return myString;
}


bool Reader::strContains(stringstream& line, string part) {
	std::size_t found = line.str().find(part);

	return (found != std::string::npos); //if found == npos, string was not found
}