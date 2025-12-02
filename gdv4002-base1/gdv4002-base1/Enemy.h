#pragma once
#include "Engine.h"
#include "player.h"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Enemy : public GameObject2D {
public:
    Enemy(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);

    void update(double tDelta);

    glm::vec3 velocity;
    float rotationSpeed;
	float knockbackDecay = 1.0f;
    bool alive = true;
    static float randomPositionX2();
    static float randomPositionY2();
    static float randomRotation2();
    static float randomSizeX2();
    static float randomSizeY2();
    static GLuint randomEnemyTexture2();
    void respawn();
    static std::vector<Enemy*> enemies;
};




extern glm::vec3 gravity;
extern Player* player;
