#pragma once
#include "MyShader.h"

class Ground {

public:
	float up, down, left, right;
	MyShader myShader;
	unsigned int vaoId;
	
	Ground(float positions[], unsigned int indices[], const char* vertexShaderPath, const char* fragmentShaderPath);
	~Ground();
	
	void Draw();
	void RemoveVao();
};