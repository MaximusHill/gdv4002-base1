#pragma once
#include "GameObject2D.h"
#include <random>

class Emitter : public GameObject2D {
private:
    float emitTimeInterval, emitCounter;
    unsigned long long particleNumber;
    GLuint bullets[8];
    std::mt19937 gen;
    std::uniform_int_distribution<int> spriteDist;
    std::uniform_real_distribution<float> normDist, massDist, scaleDist;

public:
    Emitter(glm::vec3 initPosition, glm::vec2 initSize, float emitTimeInterval);
    void update(double tDelta) override;
    void render() override;
};
