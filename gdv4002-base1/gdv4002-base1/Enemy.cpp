#include "Enemy.h"
#include <random>
#include <ctime>
#include "Engine.h"

std::vector<Enemy*> Enemy::enemies;
extern Player* player;
extern glm::vec3 gravity;

std::mt19937& getRandomEngine2() {
    static std::mt19937 engine(static_cast<unsigned int>(time(nullptr)));
    return engine;
}

Enemy::Enemy(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID),
    velocity(0.0f)
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
    if (!alive) return; // skip update if dead

    // Apply gravity
    velocity += gravity * float(tDelta);
    velocity -= velocity * knockbackDecay * float(tDelta);
    // Collision with player
    if (player && CheckAABBCollision2(player, this)) {
        glm::vec2 dir = glm::normalize(glm::vec2(position.x, position.y) -
            glm::vec2(player->position.x, player->position.y));
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
    alive = true;
    position = glm::vec3(randomPositionX2(), randomPositionY2(), 0.5f);
    orientation = randomRotation2();
    size = glm::vec2(randomSizeX2(), randomSizeY2());
    textureID = randomEnemyTexture2();
    velocity = glm::vec3(0.0f);
    std::uniform_real_distribution<float> dist(1.0f, 7.0f);
    rotationSpeed = dist(getRandomEngine2());
}
float Enemy::randomPositionX2()
{
    float planeWidth = getViewplaneWidth();
    float halfWidth = planeWidth / 2.0f;

    std::uniform_real_distribution<float> distribution(-halfWidth, halfWidth);

    return distribution(getRandomEngine2());
}
float Enemy::randomPositionY2()
{
    float planeHeight = getViewplaneHeight();
    float halfHeight = planeHeight / 2.0f;

    // Top 10% starts at 90% of the positive range so that the enemys spawn near the top
    float startY = halfHeight * 0.90f;
    float endY = halfHeight;

    std::uniform_real_distribution<float> distribution(startY, endY);

    return distribution(getRandomEngine2());
}
float Enemy::randomRotation2()
{
    std::uniform_real_distribution<float> distribution(0.0f, 360.0f);

    return distribution(getRandomEngine2());
}

float Enemy::randomSizeX2()
{
    std::uniform_real_distribution<float> distribution(0.3, 1.5);

    return distribution(getRandomEngine2());
}
float Enemy::randomSizeY2()
{
    std::uniform_real_distribution<float> distribution(0.3, 1.5);

    return distribution(getRandomEngine2());
}
GLuint Enemy::randomEnemyTexture2()
{


    std::uniform_int_distribution<int> distribution(0, 2);

    float engine = distribution(getRandomEngine2());

    if (engine == 0)
    {
        return loadTexture("Resources\\Textures\\asteroid1.png");
    }
    else if (engine == 1)
    {
        return  loadTexture("Resources\\Textures\\asteroid2.png");
    }
    else if (engine == 2)
    {
        return loadTexture("Resources\\Textures\\asteroid3.png");
    }
    else
    {
        return 0;
    }


}
