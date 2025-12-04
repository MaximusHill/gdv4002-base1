#pragma once

#include "GameObject2D.h"

class Player : public GameObject2D {

private:

	float		mass;
	


public:

	Player(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
	glm::vec3	velocity;
	void update(double tDelta) override;
	glm::vec3 getVelocity() const { return velocity; }
	float collisionCooldown = 0.0f;
	float boostCooldown = 2.0f;
	
	bool boosted = false;

};
