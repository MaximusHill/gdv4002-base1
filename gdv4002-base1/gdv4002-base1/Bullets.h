#pragma once
#pragma once
#include "GameObject2D.h"

class Bullets : public GameObject2D {
private:
    float mass;
    glm::vec3 velocity;
    bool hitRegistered = false;

public:
   Bullets(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
    void update(double tDelta) override;

    static int points;
};
