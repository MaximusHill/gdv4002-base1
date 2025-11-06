#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <string.h>
#include <conio.h>
// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

std::bitset<5> keys{ 0x0 };

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
	setKeyboardHandler(myKeyboardHandler);


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}



void myUpdate(GLFWwindow* window, double tDelta) {

	static float playerSpeed = 1.0f; // distance per second
	float playerRotationSpeed = glm::radians(90.0f);
	GameObject2D* player = getObject("player1");

	if (keys.test(Key::W) == true) {

		player->position.y += playerSpeed * (float)tDelta;
	}
	
	if (keys.test(Key::S) == true) {

		player->position.y -= playerSpeed * (float)tDelta;
	}
	if (keys.test(Key::A) == true) {

		player->orientation += playerRotationSpeed * tDelta;
	}
	if (keys.test(Key::D) == true) {

		player->orientation -= playerRotationSpeed * tDelta;
	}

	float player2RotationSpeed = glm::radians(90.0f);
	GameObject2D* player2 = getObject("player2");
	player2->orientation += player2RotationSpeed * tDelta;
}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if the key was just pressed
	if (action == GLFW_PRESS) {

		// now check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			
				glfwSetWindowShouldClose(window, true);
			break;
		
		case GLFW_KEY_W:
			keys[Key::W] = true;
			break;
		case GLFW_KEY_S:
			keys[Key::S] = true;
			break;

		case GLFW_KEY_A:
			keys[Key::A] = true;
			break;
		case GLFW_KEY_D:
			keys[Key::D] = true;
			break;

		}

	}
	// If not pressed, check the key has just been released
	else if (action == GLFW_RELEASE) {
		switch (key)
		{
		
		
		case GLFW_KEY_W:
			keys[Key::W] = false;
			break;
		case GLFW_KEY_S:
			keys[Key::S] = false;
			break;
		case GLFW_KEY_A:
			keys[Key::A] = false;
			break;
		case GLFW_KEY_D:
			keys[Key::D] = false;
			break;

		}

		// handle key release events
	}
}
