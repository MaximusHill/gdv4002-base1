#pragma once

#include <glm/glm.hpp>
#include "GameObject2D.h"
class Lives : public GameObject2D {

private:

public:
	Lives(glm::vec3 initPosition,float initOrientation, glm::vec2 initSize, GLuint initTextureID);

	void update(double tDelta)override;

};