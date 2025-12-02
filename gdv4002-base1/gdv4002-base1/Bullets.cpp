#include "Bullets.h"
#include "Engine.h"
#include "player.h"
#include "Enemy.h"
extern Player* player;
extern std::vector<Enemy*> enemies;
int Bullets::points = 0;
Bullets::Bullets(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {


    // Convert degrees to radians
    float rad = glm::radians(initOrientation);
    this->orientation = initOrientation+ glm::radians(270.0f);
    // Set velocity ONCE (direction bullet is fired)
    velocity = glm::vec3(cos(initOrientation),sin(initOrientation),0.0f) * 7.0f;
   
   
}
bool CheckAABBCollision3(GameObject2D* a, GameObject2D* b) {
    float aLeft = a->position.x - a->size.x * 0.5f;
    float aRight = a->position.x + a->size.x * 0.5f;
    float aTop = a->position.y + a->size.y * 0.5f;
    float aBottom = a->position.y - a->size.y * 0.5f;

    float bLeft = b->position.x - b->size.x * 0.5f;
    float bRight = b->position.x + b->size.x * 0.5f;
    float bTop = b->position.y + b->size.y * 0.5f;
    float bBottom = b->position.y - b->size.y * 0.5f;

    return !(aLeft > bRight ||
        aRight < bLeft ||
        aTop < bBottom ||
        aBottom > bTop);
}
void Bullets::update(double tDelta) {

    // Move bullet
    position += velocity * (float)tDelta;

   
   
    if (!hitRegistered) { // only check collisions if not already hit
        for (Enemy* e : enemies) {
            if (!e) continue;

            if (CheckAABBCollision3(this, e)) {
                deleteObject(this);
                //deleteObject(e);
                points += 100;
                hitRegistered = true; // mark this bullet as already counted
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


