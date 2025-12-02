#include "Emitter.h"
#include "Engine.h"
#include "Bullets.h"
#include "player.h"

Emitter::Emitter(glm::vec3 initPosition, glm::vec2 initSize, float emitTimeInterval)
    : GameObject2D(initPosition, 0.0f, initSize, 0), emitTimeInterval(emitTimeInterval), emitCounter(emitTimeInterval), particleNumber(0) {
    for (int i = 0; i < 8; i++) {
        std::string path = "Resources\\Textures\\Snow\\snowflake" + std::to_string(i + 1) + ".png";
        bullets[i] = loadTexture(path.c_str());
    }
    std::random_device rd;
    gen = std::mt19937(rd());
    spriteDist = std::uniform_int_distribution<int>(0, 7);
    normDist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
    massDist = std::uniform_real_distribution<float>(0.005f, 0.08f);
    scaleDist = std::uniform_real_distribution<float>(0.1f, 0.5f);
}

void Emitter::render() {} // do nothing

void Emitter::update(double tDelta) {
    emitCounter += (float)tDelta;
    while (emitCounter >= emitTimeInterval) {
        emitCounter -= emitTimeInterval;
        float x = position.x + normDist(gen) * size.x;
        float y = position.y + normDist(gen) * size.y;
        float scale = scaleDist(gen);
        float mass = massDist(gen);
        float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
        int spriteIndex = spriteDist(gen);
        Bullets* s1 = new Bullets(glm::vec3(x, y,position.z), 0.0f, glm::vec2(scale, scale), bullets[spriteIndex], mass, rotationSpeed);
        std::string key = "bullet";
        if (particleNumber > 0) key += std::to_string(particleNumber);
        particleNumber++;
        addObject(key.c_str(), s1);
    }
}
