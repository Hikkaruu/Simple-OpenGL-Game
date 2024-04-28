#pragma once

#include <GLM/glm.hpp>

#include "Ground.h"

class Platform : public Ground {
public:
	Platform(float positions[], unsigned int indices[], const char* vertexShaderPath, const char* fargmentShaderPath);
	void Draw(glm::vec3 translationVector);

private:
	int numOfPlatforms;
	float originalUpPos, originalDownPos, originalRightPos, originalLeftPos;
};
