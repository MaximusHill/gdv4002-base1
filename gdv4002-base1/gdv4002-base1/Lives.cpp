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
    // If this life has been marked for death, ensure we start the dying animation once
    if (markedForDeath && !dyingStarted) {
        // Remove the live heart sprite from the engine so the dying animation (which is rendered behind)
        // is visible before the animated Dying object starts.
        deleteObject(this);

        // find matching Dying object at same position and start it
        // Dying objects are added with keys like "DyingLeft1" etc in main.cpp so we will search object collection
        // Simpler: iterate game objects and find a Dying at same position and call start()
        // Use engine's getObjectCollection to find all objects with key "Dying"
        // But Engine doesn't provide direct access to keys here; we'll search known names "DyingLeft" and "DyingRight"

        GameObject2D* d1 = getObject("DyingLeft1");
        GameObject2D* d2 = getObject("DyingLeft2");
        GameObject2D* d3 = getObject("DyingLeft3");

        GameObject2D* r1 = getObject("DyingRight1");
        GameObject2D* r2 = getObject("DyingRight2");
        GameObject2D* r3 = getObject("DyingRight3");

        Dying* candidates[6] = { (Dying*)d1, (Dying*)d2, (Dying*)d3, (Dying*)r1, (Dying*)r2, (Dying*)r3 };

        for (int i = 0; i < 6; ++i) {
            Dying* dd = candidates[i];
            if (!dd) continue;
            // compare positions (exact match used in setup)
            if (dd->position == this->position) {
                dd->start();
            }
        }

        dyingStarted = true;
    }

    // Only actually remove the visual heart sprite after dying animation has started and finished.
    // Lives no longer deletes objects directly here; Game flow will remove Life sprite when appropriate.

}

void Lives::loseLife() {
    if (lifeCount <= 0) return;

    // decrease count
    lifeCount--;

    // Find the bottom-most alive heart (smallest y; if equal, smallest x) — reversed from previous top-most selection
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
