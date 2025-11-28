#pragma once

#include "GameObject2D.h"
#include <glm/glm.hpp>

enum class ButtonAction { PLAY, EXIT, NONE };

class Button : public GameObject2D {
  public:
    Button(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID,
           ButtonAction action = ButtonAction::NONE)
        : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {
        usesAlpha = true;
        this->action = action;
    }

    // returns true if the 2D point (in viewplane coordinates) is inside the button
    bool containsPoint(const glm::vec2& point) const {
        float left = position.x - size.x * 0.5f;
        float right = position.x + size.x * 0.5f;
        float bottom = position.y - size.y * 0.5f;
        float top = position.y + size.y * 0.5f;

        return (point.x >= left && point.x <= right && point.y >= bottom && point.y <= top);
    }

    ButtonAction action = ButtonAction::NONE;
};
