#pragma once
#include "GameObject2D.h"
#include <vector>
class Lives : public GameObject2D {
public:
    Lives(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID);

    void update(double tDelta) override;
    void loseLife();          
    int getLives() const;
    static std::vector<Lives*> lives;
    int lifeCount = 3;
    bool markedForDeath = false; // scheduled to play dying animation
    bool dyingStarted = false;   // animation has been started
    bool isAlive = true; // true while heart is visible
private:
   
};