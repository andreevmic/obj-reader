#include "objreader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

void Model::countElements(const char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.compare(0, 2, "v ") == 0) {
			vertexCount++;
		}
		else if (line.compare(0, 3, "vt ") == 0) {
			textureCount++;
		}
		else if (line.compare(0, 3, "vn ") == 0) {
			normalCount++;
		}
		else if (line.compare(0, 2, "f ") == 0) {
			faceCount++;
		}
	}
}

void Model::parseVertex(const std::string& line) {
	if (line.compare(0, 2, "v ") == 0) {
		Vertex vertex;
		std::istringstream iss(line.substr(2));
		iss >> vertex.x >> vertex.y >> vertex.z;
		vertices.push_back(vertex);
	}
}

void Model::parseTextureCoord(const std::string& line) {
	if (line.compare(0, 3, "vt ") == 0) {
		TextureCoord texcoord;
		std::istringstream iss(line.substr(3));
		iss >> texcoord.u >> texcoord.v;
		textures.push_back(texcoord);
	}
}

void Model::parseNormal(const std::string& line) {
	if (line.compare(0, 3, "vn ") == 0) {
		Normal normal;
		std::istringstream iss(line.substr(3));
		iss >> normal.nx >> normal.ny >> normal.nz;
		normals.push_back(normal);
	}
}

void Model::parseFace(const std::string& line) {
	if (line.compare(0, 2, "f ") == 0) {
		Face face;
		std::istringstream iss(std::string(line).substr(2));
		std::string vertex;
		while (iss >> vertex) {
			std::stringstream vertexStream(vertex);
			std::string index;

			std::getline(vertexStream, index, '/');
			face.vertexIndices.push_back(std::stoi(index) - 1); // -1 to reduce to 0

			if (std::getline(vertexStream, index, '/')) {
				face.textureIndices.push_back(std::stoi(index) - 1); // -1 to reduce to 0
			}

			if (std::getline(vertexStream, index, '/')) {
				face.normalIndices.push_back(std::stoi(index) - 1); // -1 to reduce to 0
			}
		}
		faces.push_back(face);
	}
}

void Model::loadData(const char* filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Îøèáêà ïðè îòêðûòèè ôàéëà!" << std::endl;
		return;
	}

	std::string line;
	char prefix;

	int vertexCount = 0, textureCount = 0, normalCount = 0, faceCount = 0;

	// Ñounting the number of elements
	countElements(filename, vertexCount, textureCount, normalCount, faceCount);

	// Memory reservation
	vertices.reserve(vertexCount);
	textures.reserve(textureCount);
	normals.reserve(normalCount);
	faces.reserve(faceCount);

	while (std::getline(file, line)) {
		parseVertex(line); // Parsing vertexes
		parseTextureCoord(line); // Parsing texture coordinates
		parseNormal(line); // Parsing normals
		parseFace(line); // Parsing faces
	}
}

void Model::addVertex(const Vertex& vertex) {
	vertices.push_back(vertex);
}

void Model::addTextureCoord(const TextureCoord& texCoord) {
	textures.push_back(texCoord);
}

void Model::addNormal(const Normal& normal) {
	normals.push_back(normal);
}

void Model::addFace(const Face& face) {
	faces.push_back(face);
}