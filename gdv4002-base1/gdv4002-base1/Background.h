#pragma once

#include <glm/glm.hpp>
#include "GameObject2D.h"
class Background : public GameObject2D {

private:
	

public:
	Background(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);

	void update(double tDelta)override;

};