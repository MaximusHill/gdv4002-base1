#include "Engine.h"
#include "Background.h"
#include "GameObject2D.h"
#include "Player.h"
extern glm::vec3 gravity;
extern Player* player; 

Background::Background(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
 : GameObject2D(initPosition, initOrientation, initSize, initTextureID){
	
}
void Background::update(double tDelta) {
	usesAlpha = false;
	glm::vec3 F = glm::vec3(0.0f, 0.0f,0.0f);

	F += gravity;

	
	float width = getViewplaneWidth();
	float height = getViewplaneHeight();

	if (position.x < -width) position.x += 2 * width;
	if (position.x > width)  position.x -= 2 * width;
	if (position.y < -height) position.y += 2 * height;
	if (position.y > height)  position.y -= 2 * height;

	if (player != nullptr) {
		float parallaxFactorX = 0.2f; 
		float parallaxFactorY = 0.2f;
		position.y += player->getVelocity().y * (float)tDelta * parallaxFactorY;
		position.x += player->getVelocity().x * (float)tDelta * parallaxFactorX;
	}
}