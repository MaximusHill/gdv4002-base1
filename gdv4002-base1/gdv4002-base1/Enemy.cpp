#include "Enemy.h"
#include <random>
#include <ctime>


std::vector<Enemy*> Enemy::enemies;
extern Player* player;
extern glm::vec3 gravity;

// Random engine for rotation speed
std::mt19937& getRandomEngine2() {
    static std::mt19937 engine(static_cast<unsigned int>(time(nullptr)));
    return engine;
}

Enemy::Enemy(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID),
    velocity(0.0f) // initialize per-enemy velocity
{
    std::uniform_real_distribution<float> dist(1.0f, 7.0f);
    rotationSpeed = dist(getRandomEngine2());

    enemies.push_back(this);
}

bool CheckAABBCollision2(GameObject2D* a, GameObject2D* b) {
    float aLeft = a->position.x - a->size.x * 0.5f;
    float aRight = a->position.x + a->size.x * 0.5f;
    float aTop = a->position.y + a->size.y * 0.5f;
    float aBottom = a->position.y - a->size.y * 0.5f;

    float bLeft = b->position.x - b->size.x * 0.5f;
    float bRight = b->position.x + b->size.x * 0.5f;
    float bTop = b->position.y + b->size.y * 0.5f;
    float bBottom = b->position.y - b->size.y * 0.5f;

    return !(aLeft > bRight || aRight < bLeft || aTop < bBottom || aBottom > bTop);
}

void Enemy::update(double tDelta) {
    
    // Apply gravity to this enemy's velocity
    velocity += gravity * float(tDelta);

    // Collision with player — only affects this enemy
    if (player && CheckAABBCollision2(player, this)) {
        glm::vec2 dir = glm::normalize(glm::vec2(position.x, position.y) -
            glm::vec2(player->position.x, player->position.y));
        float knockbackForce = 2.0f;

        velocity += glm::vec3(dir.x, dir.y, 0.0f) * knockbackForce; // only this enemy
        player->velocity += glm::vec3(-dir.x, -dir.y, 0.0f) * 0.5f;
		rotationSpeed += 1.5f;
    }

    // Update position using this enemy's velocity
    position += velocity * float(tDelta);

    // Apply friction/decay so knockback slows down
    velocity -= velocity * knockbackDecay * float(tDelta);

    // Wrap around viewplane
    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;

    if (position.y < -halfHeight) position.y += getViewplaneHeight();
    if (position.y > halfHeight) position.y -= getViewplaneHeight();
    if (position.x < -halfWidth) position.x += getViewplaneWidth();
    if (position.x > halfWidth) position.x -= getViewplaneWidth();

    // Rotate enemy
    orientation += rotationSpeed * float(tDelta);
}
