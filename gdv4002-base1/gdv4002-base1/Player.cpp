#include "Keys.h"
#include <bitset>
#include "Player.h"
#include "GameObject2D.h"
#include "Engine.h"
#include "Background.h"
#include "Enemy.h"
#include <vector>
#include "Lives.h"
#include "GameState.h"
#include "Bullets.h"
#include "Collision.h"
#pragma region externals and variables



Player* player;
std::bitset<8> keys{ 0x0 };
extern std::vector<Enemy*> enemies;
extern std::vector<Bullets*> bullets;
enum class GameState;
extern GameState currentGameState;
bool canShoot = true;

#pragma endregion



Player::Player(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

    this->mass = mass;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::update(double tDelta) {
    
    glm::vec3 F = glm::vec3(0.0f, 0.0f, 0.0f);
    const float thrust = 3.0f;
    glm::vec3 offset = glm::vec3(cos(player->orientation), sin(player->orientation), 0.0f) * 0.2f;
 
    //bottom
    if (position.y < -getViewplaneHeight() / 2.0f) {

        position.y += getViewplaneHeight();
    }
    //left
    if (position.x < -getViewplaneWidth() / 2.0f) {

        position.x += getViewplaneWidth();
    }
    //top
    if (position.y > getViewplaneHeight() / 2.0f) {
        position.y -= getViewplaneHeight();
    }
    //right
    if (position.x > getViewplaneWidth() / 2.0f) {
        position.x -= getViewplaneWidth();
    }

    #pragma region keyboardhandling


    if (currentGameState == GameState::PLAYING) {
        if (keys.test(Key::W)) {
            F += glm::vec3(0.0f, thrust, 0.0f);
            orientation = glm::radians(90.0f);  

        }
        if (keys.test(Key::S)) {
            F += glm::vec3(0.0f, -thrust, 0.0f);
            orientation = glm::radians(-90.0f);  

        }
        if (keys.test(Key::A)) {
            F += glm::vec3(-thrust, 0.0f, 0.0f);
            orientation = glm::radians(180.f);
        }
        if (keys.test(Key::D)) {
            F += glm::vec3(thrust, 0.0f, 0.0f);
            orientation = glm::radians(360.0f);
        }
        if (keys.test(Key::SPACE) && canShoot) {
            GLuint bulletTexture = loadTexture("Resources/Textures/projectiles/projectile1.png");

            Bullets* b = new Bullets(
                player->position + offset,  // spawn in front
                player->orientation,
                glm::vec2(0.2f, 0.5f),
                bulletTexture,
                0.1f
            );

            addObject("bullet", b);
            bullets.push_back(b);
			
			canShoot = false;
        }
        else if (!keys.test(Key::SPACE)) {
            canShoot = true;  
        }
        if (keys.test(Key::Q)) {
            orientation += glm::radians(180.0f) * (float)tDelta;
        }
        if (keys.test(Key::E)) {
            orientation -= glm::radians(180.0f) * (float)tDelta;
        }
        
        
        if (keys.test(Key::LSHIFT) && boostCooldown == 0.0f&&boostCooldown2>0.0f)
        {

            velocity += velocity * 1.1f * (float)tDelta;
            boosted = true;
           

        }
        else if (!keys.test(Key::LSHIFT) && boosted == true) {
            

            boostCooldown = 5.0f;
            boostCooldown2 = 2.0f;
            
        }
        if (boostCooldown > 0.0f) {
            boostCooldown -= static_cast<float>(tDelta);
            if (boostCooldown < 0.0f) boostCooldown = 0.0f; boosted = false;;
        }
        if ((boostCooldown2 > 0.0f) && boosted == true) {
            boostCooldown2 -= static_cast<float>(tDelta);
            if (boostCooldown2 < 0.0f) boostCooldown2 = 0.0f;
        }
        printf("Cooldown1:%f\n", boostCooldown);
        printf("Cooldown2:%f\n", boostCooldown2);
            
		
    }
#pragma endregion

    glm::vec3 a = F * (1.0f / mass);
    velocity = velocity + (a * (float)tDelta);
    position = position + (velocity * (float)tDelta);

    if (collisionCooldown > 0.0f) {
        collisionCooldown -= static_cast<float>(tDelta);
        if (collisionCooldown < 0.0f) collisionCooldown = 0.0f;
    }
    for(Enemy * e : enemies) {
        if (!e) continue;

        if (CheckAABBCollision(this, e) && collisionCooldown <= 0.0f) {
            glm::vec2 dir = glm::normalize(glm::vec2(position.x, position.y) - glm::vec2(e->position.x, e->position.y));

            float knockbackForce = 0.5f;
            velocity += glm::vec3(dir.x, dir.y, 0.0f) * knockbackForce;

            if (!Lives::lives.empty()) {
                Lives::lives[0]->loseLife();
            }

            
            collisionCooldown = 0.1f;
        }
    }
}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Handle global keys regardless of state
    if (action == GLFW_PRESS) {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            return;

        }

    }


    // Movement keys only meaningful during PLAYING
    if (currentGameState != GameState::PLAYING) return;

    if (action == GLFW_PRESS) {
        switch (key)
        {
        case GLFW_KEY_W:    
            keys[Key::W] = true; break;
        case GLFW_KEY_S:     
            keys[Key::S] = true; break;
        case GLFW_KEY_A:     
            keys[Key::A] = true; break;
        case GLFW_KEY_D:    
            keys[Key::D] = true; break;
        case GLFW_KEY_SPACE: 
            keys[Key::SPACE] = true; break;
        case GLFW_KEY_Q:
			keys[Key::Q] = true; break;
        case GLFW_KEY_E:
            keys[Key::E] = true; break;
        case GLFW_KEY_LEFT_SHIFT:
            keys[Key::LSHIFT] = true; break;
        }
    }
    else if (action == GLFW_RELEASE) {
        switch (key)
        {
        case GLFW_KEY_W:     
            keys[Key::W] = false; break;
        case GLFW_KEY_S:    
            keys[Key::S] = false; break;
        case GLFW_KEY_A:   
            keys[Key::A] = false; break;
        case GLFW_KEY_D:  
            keys[Key::D] = false; break;
        case GLFW_KEY_SPACE:
            keys[Key::SPACE] = false; break;
        case GLFW_KEY_Q:
            keys[Key::Q] = false; break;
        case GLFW_KEY_E:
            keys[Key::E] = false; break;
        case GLFW_KEY_LEFT_SHIFT:
            keys[Key::LSHIFT] = false; break;
        }
    }
}
