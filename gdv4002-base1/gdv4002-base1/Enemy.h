#pragma once

#include "GameObject2D.h"
#include <glm/glm.hpp>

class Enemy : public GameObject2D {

private:
	

public:
	Enemy(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity);

	void update(double tDelta) override;

};
