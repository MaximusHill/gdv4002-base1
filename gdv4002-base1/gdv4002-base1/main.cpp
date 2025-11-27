#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <string.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include <random>
#include "Background.h"
#include "Lives.h"
#include "glPrint.h"
extern Player* player;
// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
glm::vec3 gravity = glm::vec3(0.0f, -2.3f,0.0f);
float randomPositionX();
float randomPositionY();
float randomSizeX();
float randomSizeY();
float randomRotation();
GLuint randomEnemyTexture();

int main(void) {
	
	hideAxisLines();
	
	float playerVelocity = 2.0f;
	
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	setViewplaneWidth(10.0f);
	float backGroundHeight = getViewplaneHeight();
	float backGroundWidth = getViewplaneWidth();
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult;
	}


	GLuint backgroundTexture = loadTexture("Resources\\Textures\\background3.png");

	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");
	
	Player* mainPlayer = new Player(glm::vec3(0.0f, 0.0f,0.5f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 0.5f);
	player = mainPlayer;
	addObject("player", mainPlayer);

	Background* background = new Background(glm::vec3(0.0f, 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundLeft = new Background(glm::vec3(getViewplaneWidth(), 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundRight = new Background(glm::vec3(-getViewplaneWidth(), 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundTop = new Background(glm::vec3(0.0f, getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundBottom = new Background(glm::vec3(0.0f, -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundTopLeft = new Background(glm::vec3(-getViewplaneWidth(), getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundTopRight = new Background(glm::vec3(getViewplaneWidth(), getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundBottomLeft = new Background(glm::vec3(-getViewplaneWidth(), -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	Background* backgroundBottomRight = new Background(glm::vec3(getViewplaneWidth(), -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

	addObject("background", background);
	addObject("backgroundLeft", backgroundLeft);
	addObject("backgroundRight", backgroundRight);
	addObject("backgroundTop", backgroundTop);
	addObject("backgroundBottom", backgroundBottom);
	addObject("backgroundTopLeft", backgroundTopLeft);
	addObject("backgroundTopRight", backgroundTopRight);
	addObject("backgroundBottomLeft", backgroundBottomLeft);
	addObject("backgroundBottomRight", backgroundBottomRight);

	GLuint AliveTexture = loadTexture("Resources\\Textures\\Alive.png");

	GLuint DeadTexture = loadTexture("Resources\\Textures\\Dead.png");
	
	Lives* Life3 = new Lives(glm::vec3(getViewplaneWidth()-5.5f, getViewplaneHeight()- 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

	Lives* Life2 = new Lives(glm::vec3(getViewplaneWidth()-6.5f, getViewplaneHeight() - 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

	Lives* Life1 = new Lives(glm::vec3(getViewplaneWidth()-7.5f, getViewplaneHeight() - 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

	addObject("Life1", Life1);
	addObject("Life2", Life2);
	addObject("Life3", Life3);

	Enemy* enemy1 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(),0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture() , 0.0f, glm::radians(0.0f));

	Enemy* enemy2 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(),0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture(), 0.0f, glm::radians(0.0f));

	Enemy* enemy3 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(),0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture(), 0.0f, glm::radians(0.0f));
	
	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);
	


	setUpdateFunction(myUpdate);

	
	setKeyboardHandler(myKeyboardHandler);



	engineMainLoop();


	engineShutdown();

	
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta) {
	GameObject2D* background = getObject("background");
	if (background) background->update(tDelta);

	GameObject2D* backgroundLeft = getObject("backgroundLeft");
	if (backgroundLeft) backgroundLeft->update(tDelta);

	GameObject2D* backgroundRight = getObject("backgroundRight");
	if (backgroundRight) backgroundRight->update(tDelta);

	GameObject2D* backgroundTop = getObject("backgroundTop");
	if (backgroundTop) backgroundTop->update(tDelta);

	GameObject2D* backgroundBottom = getObject("backgroundBottom");
	if (backgroundBottom) backgroundBottom->update(tDelta);

	GameObject2D* backgroundTopLeft = getObject("backgroundTopLeft");
	if (backgroundTopLeft) backgroundTopLeft->update(tDelta);

	GameObject2D* backgroundTopRight = getObject("backgroundTopRight");
	if (backgroundTopRight) backgroundTopRight->update(tDelta);

	GameObject2D* backgroundBottomLeft = getObject("backgroundBottomLeft");
	if (backgroundBottomLeft) backgroundBottomLeft->update(tDelta);

	GameObject2D* backgroundBottomRight = getObject("backgroundBottomRight");
	if (backgroundBottomRight) backgroundBottomRight->update(tDelta);

	GameObject2D* Life1 = getObject("Life1");
	if (Life1) Life1->update(tDelta);

	GameObject2D* Life2 = getObject("Life2");
	if (Life2) Life2->update(tDelta);

	GameObject2D* Life3 = getObject("Life3");
	if (Life3) Life3->update(tDelta);

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
GLuint randomEnemyTexture()
{
	

	std::uniform_int_distribution<int> distribution(0, 2);

	float engine = distribution(getRandomEngine());

	if (engine == 0)
	{
		return loadTexture("Resources\\Textures\\asteroid1.png");
	}
	else if (engine == 1)
	{
		return  loadTexture("Resources\\Textures\\asteroid2.png");
	}
	else if (engine == 2)
	{
		 return loadTexture("Resources\\Textures\\asteroid3.png");
	}
	else
	{
		return 0;
	}

	
}

