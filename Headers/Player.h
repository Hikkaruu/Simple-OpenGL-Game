#pragma once

#include "Platform.h"
#include "MyShader.h"

enum Movement { SPACE, A, D };

class Player {

public:
	void Create(float positions[], const char* vertexShaderPath, const char* fragmentShaderPath, float radius, int vertices);
	void Move(Movement moveKey, float timeDelta);
	void Draw(float timeDelta, int platformNumber, std::vector<Platform>& platforms);
	void RemoveVao();

private:
	MyShader myShader;
	unsigned int vaoId;
	int verticesNumber;
	float cRadius;
	glm::vec3 playerPosition;
	const float gravity = 0.0025f;
	float velX = 0.4f;
	float velY = 0.0f;
	float farBottomPos;
	float farTopPos;
	float farRightPos;
	float farLeftPos;
	float closeX;
	float closeY;
	float farX;
	float farY;
	bool canJump = false;
	const float groundUpperline = -0.8f;
	void Collision(Platform platform);
	bool CheckCollision(Platform platform);
};

