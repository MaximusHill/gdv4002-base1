#include "Engine.h"
#include "Background.h"
#include "GameObject2D.h"
#include "Player.h"
extern glm::vec3 gravity;

Background::Background(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
 : GameObject2D(initPosition, initOrientation, initSize, initTextureID){
}
void Background::update(double tDelta) {

	glm::vec3 F = glm::vec3(0.0f, 0.0f,0.0f);

	F += gravity;

	position.y = position.y += F.y * (float)tDelta;
	if (position.y < -getViewplaneHeight() / 2.0f) {

		position.y += getViewplaneHeight();
	}
	
}