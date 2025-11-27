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

    glm::vec3 velocity;           // each enemy has its own velocity
    float rotationSpeed;
    float knockbackDecay = 5.0f;  // how fast knockback slows down

    static std::vector<Enemy*> enemies;
};




extern glm::vec3 gravity;
extern Player* player;
