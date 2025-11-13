
#include "Keys.h"
#include <bitset>
#include "Player.h"
#include "GameObject2D.h"

std::bitset<5> keys{ 0x0 };
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}
void Player::update(double tDelta) {

	// Unlike our myUpdate function, we're already 'in' the player object, so no need to call getObject as we did before :)
	glm::vec2 F = glm::vec2(0.0f, 0.0f);
	glm::vec2 a = F * (1.0f / mass);
	velocity = velocity + (a * (float)tDelta);
	position = position + (velocity * (float)tDelta);
	const float thrust = 2.0f;

	// 1. accumulate forces
	if (keys.test(Key::W) == true) {

		F += glm::vec2(0.0f, thrust);
	}
	if (keys.test(Key::S) == true) {

		F += glm::vec2(0.0f, -thrust);
	}
	if (keys.test(Key::A) == true) {

		F += glm::vec2(-thrust, 0.0f);
	}
	if (keys.test(Key::D) == true) {

		F += glm::vec2(thrust, 0.0f);
	}

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
