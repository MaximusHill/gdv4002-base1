#pragma once

#include "GameObject2D.h"

class Player : public GameObject2D {

private:

	float		mass;
	glm::vec3	velocity;


public:

	Player(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);

	void update(double tDelta) override;
	glm::vec3 getVelocity() const { return velocity; }
};
