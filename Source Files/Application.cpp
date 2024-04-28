#include <string>
#include <iostream>
#include <vector>

#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include "GLM/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

#include "Player.h"
#include "MyShader.h"
#include "Ground.h"
#include "Platform.h"


GLFWwindow *window;

unsigned int screenWidth  = 1024;
unsigned int screenHeight = 768;

float delta = 0.0f;
float lastFrame = 0.0f;
void MyGladInit();
void MyGlfwInit();

// Ground
unsigned int rectangleIndices[6];
float groundVertices[4 * 3]; 

// Platforms
const int platformNumber = 6;
float platformsVertices[4 * 3]; 
glm::vec3 platformsPositions[platformNumber];

// Player
Player player;
const float circleRadius = 0.065f;
const int circleVerticesNumber = 30;
float circleVertices[(circleVerticesNumber + 1) * 3];


int main () {

	MyGlfwInit(); 
	if (window == NULL) return -1;

	MyGladInit(); 

	// Player Start
	float degree = 0.0f;

	for (int idx = 0; idx < 3 * circleVerticesNumber; idx += 3, degree += 360.0f / circleVerticesNumber) {
		circleVertices[idx + 0] = (circleRadius * (float)std::cos(glm::radians(degree)));
		circleVertices[idx + 1] = (circleRadius * (float)std::sin(glm::radians(degree)));
		circleVertices[idx + 2] = 0.0f;
	}

	circleVertices[3 * circleVerticesNumber + 0] = 0.0f;
	circleVertices[3 * circleVerticesNumber + 1] = 0.0f;
	circleVertices[3 * circleVerticesNumber + 2] = 0.0f;
	// Player End

	player.Create(circleVertices, "Shaders/playerShader.vs", "Shaders/playerShader.fs", circleRadius, circleVerticesNumber);
	
	// Ground Start
	groundVertices[0] = -1.0f;
	groundVertices[1] = -1.0f;
	groundVertices[2] = 0.0f;
	groundVertices[3] = 1.0f;
	groundVertices[4] = -1.0f;
	groundVertices[5] = 0.0f;
	groundVertices[6] = 1.0f;
	groundVertices[7] = -0.8f;
	groundVertices[8] = 0.0f;
	groundVertices[9] = -1.0f;
	groundVertices[10] = -0.8f;
	groundVertices[11] = 0.0f;

	rectangleIndices[0] = 0;
	rectangleIndices[1] = 1;
	rectangleIndices[2] = 3;
	rectangleIndices[3] = 1;
	rectangleIndices[4] = 2;
	rectangleIndices[5] = 3;

	Ground ground(groundVertices, rectangleIndices, "Shaders/groundShader.vs", "Shaders/groundShader.fs");
	// Ground End

	// Platform Start
	// 1
	platformsVertices[0] = -0.25f;
	platformsVertices[1] = -0.08f;
	platformsVertices[2] = 0.0f;
	// 2
	platformsVertices[3] = 0.25f;
	platformsVertices[4] = -0.08f;
	platformsVertices[5] = 0.0f;
	// 3
	platformsVertices[6] = 0.25f;
	platformsVertices[7] = 0.08f;
	platformsVertices[8] = 0.0f;
	// 4
	platformsVertices[9] = -0.25f;
	platformsVertices[10] = 0.08f;
	platformsVertices[11] = 0.0f;

	// translations
	platformsPositions[0] = glm::vec3(-0.8f, -0.5f, 0.0f);
	platformsPositions[1] = glm::vec3(-0.9f, -0.1f, 0.0f);
	platformsPositions[2] = glm::vec3(-0.5f, 0.65f, 0.0f);
	platformsPositions[3] = glm::vec3(1.0f, 0.2f, 0.0f);
	platformsPositions[4] = glm::vec3(0.3f, 0.55f, 0.0f);
	//platformsPositions[5] = glm::vec3(0.75f, -0.5f, 0.0f);
	
	std::vector<Platform> platforms;
	for (int i = 0; i < platformNumber; i++)
		platforms.push_back(Platform(platformsVertices, rectangleIndices, "Shaders/platformsShader.vs", "Shaders/platformsShader.fs"));
	// Platform End

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = (float)glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// BG
		glClearColor(0.529f, 0.807f, 0.921f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ground.Draw();

		for (int i = 0; i < platformNumber; i++) 
			platforms[i].Draw(platformsPositions[i]);

		// Player movement
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			player.Move(SPACE, delta);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			player.Move(D, delta);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			player.Move(A, delta);

		player.Draw(delta, platformNumber, platforms);
		
		glfwSwapBuffers(window);
		glfwPollEvents(); 
	}

	ground.RemoveVao();
	player.RemoveVao();
	glfwTerminate();
	return 0;
}

void MyGladInit() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "GLAD initialization error" << std::endl;
}

void MyGlfwInit() {

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, false);
	window = glfwCreateWindow(screenWidth, screenHeight, "Game", NULL, NULL);
	if (window == NULL) {
		std::cout << "GLFW window error" << std::endl;
		glfwTerminate();
		return;
	}
	else {
		glfwMakeContextCurrent(window);
	}
}	

