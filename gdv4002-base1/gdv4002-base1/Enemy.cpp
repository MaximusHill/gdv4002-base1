#include "Engine.h"
#include "Enemy.h"
extern glm::vec2 gravity;

Enemy::Enemy(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	phaseAngle = initialPhase;
	phaseVelocity = initialPhaseVelocity;
}
void Enemy::update(double tDelta) {
	
	glm::vec2 F = glm::vec2(0.0f, 0.0f);
	
	F += gravity;

	position.y = position.y += F.y * (float)tDelta;
	
}
