#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <string.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include <random>
#include "Background.h"
// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
glm::vec2 gravity = glm::vec2(0.0f, -0.3f);
float randomPositionX();
float randomPositionY();
float randomSizeX();
float randomSizeY();
float randomRotation();


int main(void) {
	
	float playerVelocity = 2.0f;
	
	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}
	setViewplaneWidth(10.0f);

	GLuint backgroundTexture = loadTexture("Resources\\Textures\\Background.png");

	printf("Background texture ID = %u\n", backgroundTexture);

	float backGroundHeight = getViewplaneHeight() * 1.0f;
	float backGroundWidth = getViewplaneWidth()*1.0f;

	

	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");
	
	Player* mainPlayer = new Player(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 0.5f);

	Background* background = new Background(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	addObject("background", background);

	addObject("player", mainPlayer);

	

	GLuint enemyTexture = loadTexture("Resources\\Textures\\asteroid.png");
	
	// 2. Create enemy objects
	Enemy* enemy1 = new Enemy(glm::vec2(randomPositionX(), randomPositionY()), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), enemyTexture, 0.0f, glm::radians(0.0f));


	

	Enemy* enemy2 = new Enemy(glm::vec2(randomPositionX(), randomPositionY()), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), enemyTexture, 0.0f, glm::radians(0.0f));

	

	Enemy* enemy3 = new Enemy(glm::vec2(randomPositionX(), randomPositionY()), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), enemyTexture, 0.0f, glm::radians(0.0f));
	
	// Add enemy objects to the engine
	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);
	

	
	// Option A: don't override update -> comment out the next line to use engine's default updater
	// setUpdateFunction(myUpdate);

	// Option B: if you want a custom update, keep this but implement myUpdate to forward updates
	setUpdateFunction(myUpdate);

	
	setKeyboardHandler(myKeyboardHandler);


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta) {
	GameObject2D* background = getObject("background");
	if (background) background->update(tDelta);
	
	GameObject2D* player = getObject("player");
	if (player) player->update(tDelta);

	GameObject2D* enemy1 = getObject("enemy1");
	if (enemy1) enemy1->update(tDelta);
	GameObject2D* enemy2 = getObject("enemy2");
	if (enemy2) enemy2->update(tDelta);
	GameObject2D* enemy3 = getObject("enemy3");
	if (enemy3) enemy3->update(tDelta);
}
std::mt19937& getRandomEngine() {
	static std::random_device rd;
	static std::mt19937 engine(rd());
	return engine;
}
float randomPositionX()
{
	float planeWidth = getViewplaneWidth();
	float halfWidth = planeWidth / 2.0f;

	std::uniform_real_distribution<float> distribution(-halfWidth, halfWidth);
	
	return distribution(getRandomEngine());
}
float randomPositionY()
{
	float planeHeight = getViewplaneHeight();
	float halfHeight = planeHeight / 2.0f;

	// Top 10% starts at 90% of the positive range so that the enemys spawn near the top
	float startY = halfHeight * 0.90f;
	float endY = halfHeight;

	std::uniform_real_distribution<float> distribution(startY, endY);

	return distribution(getRandomEngine());
}
float randomRotation()
{
	std::uniform_real_distribution<float> distribution(0.0f, 360.0f);

	return distribution(getRandomEngine());
}

float randomSizeX()
{
	std::uniform_real_distribution<float> distribution(0.3, 1.5);

	return distribution(getRandomEngine());
}
float randomSizeY()
{
	std::uniform_real_distribution<float> distribution(0.3, 1.5);

	return distribution(getRandomEngine());
}
