#include "Lives.h"
#include "Engine.h"
#include "Dying.h"

std::vector<Lives*> Lives::lives;
Lives::Lives(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
  
{
    
    lives.push_back(this);
}

void Lives::update(double tDelta) 
{
    
    if (markedForDeath && !dyingStarted) {
        
        deleteObject(this);

        

        GameObject2D* d1 = getObject("DyingLeft1");
        GameObject2D* d2 = getObject("DyingLeft2");
        GameObject2D* d3 = getObject("DyingLeft3");

        GameObject2D* r1 = getObject("DyingRight1");
        GameObject2D* r2 = getObject("DyingRight2");
        GameObject2D* r3 = getObject("DyingRight3");

        Dying* candidates[6] = { (Dying*)d1, (Dying*)d2, (Dying*)d3, (Dying*)r1, (Dying*)r2, (Dying*)r3 };
        //dc == dying candidate
        for (int i = 0; i < 6; ++i) {
            Dying* dc = candidates[i];
            if (!dc) continue;
            if (dc->position == this->position) {
                dc->start();
            }
        }

        dyingStarted = true;
    }

    

}

void Lives::loseLife() {
    if (lifeCount <= 0) return;

    
    lifeCount--;

    
    Lives* victim = nullptr;
    for (Lives* L : lives) {
        if (!L) continue;
        if (!L->isAlive) continue;
        if (victim == nullptr) {
            victim = L;
        }
        else {
            // reverse ordering: prefer smaller y, then smaller x
            if (L->position.y < victim->position.y ||
                (L->position.y == victim->position.y && L->position.x < victim->position.x)) {
                victim = L;
            }
        }
    }

    if (victim) {
        victim->markedForDeath = true;
        victim->isAlive = false; // ensure it's not selected again
    }
}

int Lives::getLives() const {
    return lifeCount;
}
