#pragma once

#include <vector>
#include <string>

struct Vertex {
	float x, y, z;
};

struct TextureCoord {
	float u, v;
};

struct Normal {
	float nx, ny, nz;
};

struct Face {
	std::vector<int> vertexIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;
};

// Class for storing the entire model
class Model {
public:
	std::vector<Vertex> vertices;
	std::vector<TextureCoord> textures;
	std::vector<Normal> normals;
	std::vector<Face> faces;

	void loadData(const char* filename);
	void addVertex(const Vertex& vertex);
	void addTextureCoord(const TextureCoord& texCoord);
	void addNormal(const Normal& normal);
	void addFace(const Face& face);

	void parseVertex(const std::string& line);
	void parseTextureCoord(const std::string& line);
	void parseNormal(const std::string& line);
	void parseFace(const std::string& line);

private:
	void countElements(const char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount);
};