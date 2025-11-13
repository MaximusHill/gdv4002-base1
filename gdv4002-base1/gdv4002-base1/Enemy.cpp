
#include "Enemy.h"

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

	// Set position based on phaseAngle
	position.y = sinf(phaseAngle);

	// Update phaseAngle based on velocity * time elapsed
	phaseAngle += phaseVelocity * tDelta;
}