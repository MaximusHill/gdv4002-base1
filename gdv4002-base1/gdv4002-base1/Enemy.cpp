#include "Engine.h"
#include "Enemy.h"
#include <random>
extern glm::vec3 gravity;
std::mt19937& getRandomEngine2();

Enemy::Enemy(
	glm::vec3 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	
}
void Enemy::update(double tDelta) {
	
	float randomRotationSpeed = std::uniform_real_distribution<float>(1.0f, 7.0f)(getRandomEngine2());
	glm::vec3 F = glm::vec3(0.0f, 0.0f,0.0f);
	
	F += gravity;

	position.y = position.y += F.y * (float)tDelta;

	
	//bottom
	if (position.y <-getViewplaneHeight() / 2.0f) {

		position.y += getViewplaneHeight();
	}
	//left
	if (position.x < -getViewplaneWidth() / 2.0f) {

		position.x += getViewplaneWidth();
	}
	//top
	if (position.y > getViewplaneHeight() / 2.0f) {
		position.y -= getViewplaneHeight();
	}
	//right
	if (position.x > getViewplaneWidth() / 2.0f) {
		position.x -= getViewplaneWidth();
	}
	orientation += randomRotationSpeed * tDelta;
	float top = position.y + (size.y / 2.0f);
	float bottom = position.y - (size.y / 2.0f);
	float left = position.x - (size.x / 2.0f);
	float right = position.x + (size.x / 2.0f);
}
std::mt19937& getRandomEngine2() {
	static std::random_device rd;
	static std::mt19937 engine(rd());
	return engine;
}
