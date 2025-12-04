
#include "Collision.h"
#include"GameObject2D.h"


bool CheckAABBCollision(GameObject2D* a, GameObject2D* b) {
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