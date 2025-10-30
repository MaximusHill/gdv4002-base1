#include "Engine.h"
#include <string.h>
#include <conio.h>
// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);

int main(void) {

	float playerVelocity = 2.0f;
	float anglesPerSecond = glm::radians(45.0f);
	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//
	
	addObject("player1", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\mcblock01.png", TextureProperties::NearestFilterTexture());
	GameObject2D* player1Object = getObject("player1");
	if (player1Object != nullptr) {
		player1Object->position = glm::vec2(-1.5f, 1.0f);
		player1Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");
	}

	addObject("player2", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\mcblock01.png", TextureProperties::NearestFilterTexture());
	GameObject2D* player2Object = getObject("player2");
	if (player2Object != nullptr) {
		player2Object->position = glm::vec2(0.5f, 1.0f);
		player2Object->orientation = glm::radians(-30.0f);
	}

	setUpdateFunction(myUpdate);
	
	
	setViewplaneWidth(10.0f);
	


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}



void myUpdate(GLFWwindow* window, double tDelta) {

	float player1RotationSpeed = glm::radians(90.0f);
	GameObject2D* player1 = getObject("player1");
	player1->orientation += player1RotationSpeed * tDelta;

	float player2RotationSpeed = glm::radians(90.0f);
	GameObject2D* player2 = getObject("player2");
	player2->orientation += player2RotationSpeed * tDelta;
}

