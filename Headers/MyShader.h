#pragma once

#include <GLM/glm.hpp>
#include <string>

class MyShader {

public:
	void Create(const char* vrtxPath, const char* frgmtPath);
	void Bind();
	void Unbind();
	void setFloatUniform(const std::string &name, float val);
	void setMat4Uniform(const std::string &name, const glm::mat4 &mat) const;

private:
	unsigned int shaderProgram;
};
