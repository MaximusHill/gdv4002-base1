#pragma once

#include <glm/glm.hpp>
#include "GameObject2D.h"
class Deaths : public GameObject2D {

private:

public:
	Deaths(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);

	void update(double tDelta)override;

};