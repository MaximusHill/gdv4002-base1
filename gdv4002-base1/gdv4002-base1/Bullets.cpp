#include "Bullets.h"
#include "Engine.h"
#include "Enemy.h"
#include "Collision.h"
#pragma region externs and variables



extern Player* player;
extern std::vector<Enemy*> enemies;
int Bullets::points = 0; 
#pragma endregion
Bullets::Bullets(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {


  
    
    this->orientation = initOrientation+ glm::radians(270.0f);
    // Set velocity ONCE (direction bullet is fired)
    velocity = glm::vec3(cos(initOrientation),sin(initOrientation),0.0f) * 7.0f;
   
   
}
void Bullets::update(double tDelta) {

    
    position += velocity * (float)tDelta;

   
   
    if (!hitRegistered) { 
        for (Enemy* e : enemies) {
            if (!e) continue;

            if (CheckAABBCollision(this, e)) {
                deleteObject(this);
                points += 100;
                hitRegistered = true; 
				e->alive = false;
                break; // stop after first collision
            }
        }
    }

    if (position.x < -getViewplaneWidth() / 2 || position.x > getViewplaneWidth() / 2 ||
        position.y < -getViewplaneHeight() / 2 || position.y > getViewplaneHeight() / 2) {
        deleteObject(this);
    }


}


