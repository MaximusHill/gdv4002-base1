#include "Enemy.h"
#include <random>
#include <ctime>
#include "Engine.h"
#include "Collision.h"
#include "RandomEngine.h"

 #pragma region externs and variables


std::vector<Enemy*> Enemy::enemies;
extern Player* player;
extern glm::vec3 gravity;

#pragma endregion

Enemy::Enemy(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID),
    velocity(0.0f)
{
    std::uniform_real_distribution<float> dist(1.0f, 7.0f);
    rotationSpeed = dist(getRandomEngine());
    enemies.push_back(this);
}



void Enemy::update(double tDelta) {
    if (!alive) return;

    // Apply gravity
    velocity += gravity * float(tDelta);
    velocity -= velocity * knockbackDecay * float(tDelta);

    // Collision with player
    if (player && CheckAABBCollision(player, this)) {
		//dir = Direction 
        glm::vec2 dir = glm::normalize(glm::vec2(position.x, position.y) - glm::vec2(player->position.x, player->position.y));

        float knockbackForce = 2.0f;
        velocity += glm::vec3(dir.x, dir.y, 0.0f) * knockbackForce;

        player->velocity += glm::vec3(-dir.x, -dir.y, 0.0f) * 0.5f;
        rotationSpeed += 1.5f;
    }

    // Update position
    position += velocity * float(tDelta);


    // Wrap around
    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;
    if (position.y < -halfHeight) position.y += getViewplaneHeight();
    if (position.y > halfHeight) position.y -= getViewplaneHeight();
    if (position.x < -halfWidth) position.x += getViewplaneWidth();
    if (position.x > halfWidth) position.x -= getViewplaneWidth();

    // Rotate
    orientation += rotationSpeed * float(tDelta);
}

void Enemy::respawn() {
	//reset enemy 
    alive = true;
    position = glm::vec3(randomPositionX(), randomPositionY(), 0.5f);
    orientation = randomRotation();
    size = glm::vec2(randomSizeX(), randomSizeY());
    textureID = randomEnemyTexture();
    velocity = glm::vec3(0.0f);
    std::uniform_real_distribution<float> dist(1.0f, 7.0f);
    rotationSpeed = dist(getRandomEngine());
}

