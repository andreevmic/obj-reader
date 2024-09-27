OBJ File Parser in C++

This repository contains a C++ library for parsing .obj files, a widely used format for 3D models. The parser extracts vertices, texture coordinates, normals, and face indices from OBJ files, providing an easy way to load 3D geometry data into your application.

Features:
Parses vertices (v), texture coordinates (vt), normals (vn), and faces (f).
Efficient memory allocation based on pre-counting elements in the file.
Simple and modular design for easy integration into any project.
How to Use:
Add the header and source files to your project.
Call the Model::loadData(const char* filename) function to load and parse an OBJ file.
Access the parsed data (vertices, textures, normals, and faces) through the Model class.

Feel free to contribute by improving the parser or extending its functionality!
