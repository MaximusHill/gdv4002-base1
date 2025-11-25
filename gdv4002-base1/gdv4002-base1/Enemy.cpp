#include "Engine.h"
#include "Enemy.h"
extern glm::vec3 gravity;

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
	
	glm::vec3 F = glm::vec3(0.0f, 0.0f,0.0f);
	
	F += gravity;

	position.y = position.y += F.y * (float)tDelta;

	if (position.y < -getViewplaneHeight() / 2.0f)
	{
		position.y += getViewplaneHeight();
	
	}
	
}
