#include "Emitter.h"
#include "Engine.h"
#include "Bullets.h"
#include "player.h"

extern Player* player;
Emitter::Emitter(glm::vec3 initPosition, glm::vec2 initSize, float emitTimeInterval)
    : GameObject2D(initPosition, 0.0f, initSize, 0), emitTimeInterval(emitTimeInterval), emitCounter(emitTimeInterval), particleNumber(0) {
    for (int i = 0; i < 2; i++) {
        std::string path = "Resources\\Textures\\Asteroid" + std::to_string(i + 1) + ".png";
        bullets[i] = loadTexture(path.c_str());
    }
    std::random_device rd;
    gen = std::mt19937(rd());
    spriteDist = std::uniform_int_distribution<int>(0, 4);
    
}

void Emitter::render() {} // do nothing

void Emitter::update(double tDelta) {
    emitCounter += (float)tDelta;
    while (emitCounter >= emitTimeInterval) {
        emitCounter -= emitTimeInterval;
        float x = position.x + normDist(gen) * size.x;
        float y = position.y + normDist(gen) * size.y;
		float z = 0.5f;
        float scale =0.3f;
        float mass = 1.0f;


        
        orientation == player->orientation;
        int spriteIndex = spriteDist(gen);
        Bullets* s1 = new Bullets(glm::vec3(x, y,z), 0.0f, glm::vec2(scale, scale), bullets[spriteIndex], mass);
        std::string key = "bullet";
        if (particleNumber > 0) key += std::to_string(particleNumber);
        particleNumber++;
        addObject(key.c_str(), s1);
    }
}
