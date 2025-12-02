#include "Bullets.h"
extern glm::vec3 gravity;

Bullets::Bullets(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {
	this->mass = mass;
    velocity = glm::vec3(0.0f, 2.0f,0.0f);
}

void Bullets::update(double tDelta) {
    glm::vec3 accel = gravity / mass;
    velocity += accel * (float)tDelta;
    position += velocity * (float)tDelta;
    orientation += angleChangePerSecond * (float)tDelta;
}
