#pragma once

#include <glm/glm.hpp>
#include "GameObject2D.h"
class Dying : public GameObject2D {

private:
	GLuint Texture;
	bool active = false; // only animate when activated
	float rotateSign = 0.0f; // +1 for left, -1 for right
public:
	Dying(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);

	void update(double tDelta)override;
	void render() override;

	void start(); // activate the dying animation

}; 
