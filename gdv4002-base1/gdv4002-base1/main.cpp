#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <string.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include <random>
#include "Background.h"
#include "Lives.h"
#include "glPrint.h"
#include "Deaths.h"
#include "Dying.h"
#include "GameState.h"
#include "Button.h"
#include "Bullets.h"

extern Player* player;
std::vector<Enemy*> enemies;
 std::vector<Bullets*> bullets;
std::vector<Lives*> lives;
void myRender(GLFWwindow* window);
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void myMouseButtonHandler(GLFWwindow* window, int button, int action, int mods);
glm::vec3 gravity = glm::vec3(0.0f, -0.3f,0.0f);
float randomPositionX();
float randomPositionY();
float randomSizeX();
float randomSizeY();
float randomRotation();
GLuint randomEnemyTexture();

// Game state
GameState currentGameState = GameState::MAIN_MENU;

// forward so Player.cpp keyboard handler can call this on restart

void initGameplayObjects();
void initBackgroundObjects();

// menu buttons
static Button* playButton = nullptr;
static Button* exitButton = nullptr;

int main(void) {
    
    hideAxisLines();
    
    float playerVelocity = 2.0f;
    
    int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

    setViewplaneWidth(10.0f);
    
    if (initResult != 0) {

        printf("Cannot setup game window!!!\n");
        return initResult;
    }
    

    

    // Create gameplay objects (player, lives, enemies)
    initGameplayObjects();

    // Create background objects once (don't recreate each frame)
    initBackgroundObjects();

    setKeyboardHandler(myKeyboardHandler);
    // set mouse handler
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), myMouseButtonHandler);

    // create menu buttons
    float vw = getViewplaneWidth();
    float vh = getViewplaneHeight();

    GLuint Playbtn = loadTexture("Resources\\Textures\\Play_Button2.png");
    GLuint Exitbtn = loadTexture("Resources\\Textures\\Exit_Button2.png");
    playButton = new Button(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec2(3.5f, 1.0f), Playbtn, ButtonAction::PLAY);
    exitButton = new Button(glm::vec3(0.0f, -1.5f, 0.0f), 0.0f, glm::vec2(3.5f, 1.0f), Exitbtn, ButtonAction::EXIT);
    addObject("menuPlay", playButton);
    addObject("menuExit", exitButton);

    // enable custom render to draw UI text
    setRenderFunction(myRender);
    setUpdateFunction(myUpdate);
    engineMainLoop();
   
    engineShutdown();

    
    return 0;
}
void initBackgroundObjects() {
    float backGroundHeight = getViewplaneHeight();
    float backGroundWidth = getViewplaneWidth();
    GLuint backgroundTexture = loadTexture("Resources\\Textures\\background3.png");
    Background* background = new Background(glm::vec3(0.0f, 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundLeft = new Background(glm::vec3(getViewplaneWidth(), 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundRight = new Background(glm::vec3(-getViewplaneWidth(), 0.0f, -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundTop = new Background(glm::vec3(0.0f, getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundBottom = new Background(glm::vec3(0.0f, -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundTopLeft = new Background(glm::vec3(-getViewplaneWidth(), getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundTopRight = new Background(glm::vec3(getViewplaneWidth(), getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundBottomLeft = new Background(glm::vec3(-getViewplaneWidth(), -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    Background* backgroundBottomRight = new Background(glm::vec3(getViewplaneWidth(), -getViewplaneHeight(), -0.5f), 0.0f, glm::vec2(backGroundWidth, backGroundHeight), backgroundTexture);

    addObject("background", background);
    addObject("backgroundLeft", backgroundLeft);
    addObject("backgroundRight", backgroundRight);
    addObject("backgroundTop", backgroundTop);
    addObject("backgroundBottom", backgroundBottom);
    addObject("backgroundTopLeft", backgroundTopLeft);
    addObject("backgroundTopRight", backgroundTopRight);
    addObject("backgroundBottomLeft", backgroundBottomLeft);
    addObject("backgroundBottomRight", backgroundBottomRight);
}

void initGameplayObjects() {

   
    GLuint playerTexture = loadTexture("Resources\\Textures\\spaceship3.png");
    
    Player* mainPlayer = new Player(glm::vec3(0.0f, 0.0f,0.5f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 0.5f);
    player = mainPlayer;
    addObject("player", mainPlayer);
  
    GLuint AliveTexture = loadTexture("Resources\\Textures\\Alive.png");

    GLuint DeadTexture = loadTexture("Resources\\Textures\\Dead.png");
    
    Lives* Life3 = new Lives(glm::vec3(getViewplaneWidth()-5.5f, getViewplaneHeight()- 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

    Lives* Life2 = new Lives(glm::vec3(getViewplaneWidth()-6.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

    Lives* Life1 = new Lives(glm::vec3(getViewplaneWidth()-7.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), AliveTexture);

    lives.push_back(Life1);
    lives.push_back(Life2);
    lives.push_back(Life3);
    addObject("Life1", Life1);
    addObject("Life2", Life2);
    addObject("Life3", Life3); 
    
    Dying* DyingLeft3 = new Dying(glm::vec3(getViewplaneWidth() - 5.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\Dyingleft.png"));

    Dying* DyingLeft2 = new Dying(glm::vec3(getViewplaneWidth() - 6.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\Dyingleft.png"));

    Dying* DyingLeft1 = new Dying(glm::vec3(getViewplaneWidth() - 7.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\Dyingleft.png"));

    addObject("DyingLeft1", DyingLeft1);
    addObject("DyingLeft2", DyingLeft2);
    addObject("DyingLeft3", DyingLeft3);

    Dying* DyingRight3 = new Dying(glm::vec3(getViewplaneWidth() - 5.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\DyingRight.png"));

    Dying* DyingRight2 = new Dying(glm::vec3(getViewplaneWidth() - 6.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\DyingRight.png"));

    Dying* DyingRight1 = new Dying(glm::vec3(getViewplaneWidth() - 7.5f, getViewplaneHeight() - 5.5f, -0.4f), 0.0f, glm::vec2(0.5f, 0.5f), loadTexture("Resources\\Textures\\DyingRight.png"));

    addObject("DyingRight1", DyingRight1);
    addObject("DyingRight2", DyingRight2);
    addObject("DyingRight3", DyingRight3);

    Deaths* Death3 = new Deaths(glm::vec3(getViewplaneWidth() - 5.5f, getViewplaneHeight() - 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), DeadTexture);

    Deaths* Death2 = new Deaths(glm::vec3(getViewplaneWidth() - 6.5f, getViewplaneHeight() - 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), DeadTexture);

    Deaths* Death1 = new Deaths(glm::vec3(getViewplaneWidth() - 7.5f, getViewplaneHeight() - 5.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), DeadTexture);

    addObject("Death1", Death1);
    addObject("Death2", Death2);
    addObject("Death3", Death3);
    
    
    Enemy* enemy1 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(), 0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture());

    Enemy* enemy2 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(), 0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture());

    Enemy* enemy3 = new Enemy(glm::vec3(randomPositionX(), randomPositionY(), 0.5f), randomRotation(), glm::vec2(randomSizeX(), randomSizeY()), randomEnemyTexture());


    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    
    addObject("enemy1", enemy1);
	
    
    addObject("enemy2", enemy2);
    
   
    addObject("enemy3", enemy3);
    
  
    
}


void myUpdate(GLFWwindow* window, double tDelta) {
    // Always update background elements so menu has motion
    GameObject2D* background = getObject("background");
    if (background) background->update(tDelta);

    GameObject2D* backgroundLeft = getObject("backgroundLeft");
    if (backgroundLeft) backgroundLeft->update(tDelta);

    GameObject2D* backgroundRight = getObject("backgroundRight");
    if (backgroundRight) backgroundRight->update(tDelta);

    GameObject2D* backgroundTop = getObject("backgroundTop");
    if (backgroundTop) backgroundTop->update(tDelta);

    GameObject2D* backgroundBottom = getObject("backgroundBottom");
    if (backgroundBottom) backgroundBottom->update(tDelta);

    GameObject2D* backgroundTopLeft = getObject("backgroundTopLeft");
    if (backgroundTopLeft) backgroundTopLeft->update(tDelta);

    GameObject2D* backgroundTopRight = getObject("backgroundTopRight");
    if (backgroundTopRight) backgroundTopRight->update(tDelta);

    GameObject2D* backgroundBottomLeft = getObject("backgroundBottomLeft");
    if (backgroundBottomLeft) backgroundBottomLeft->update(tDelta);

    GameObject2D* backgroundBottomRight = getObject("backgroundBottomRight");
    if (backgroundBottomRight) backgroundBottomRight->update(tDelta);

    // If not playing, skip gameplay updates
    if (currentGameState != GameState::PLAYING) {
        return;
    }

    GameObject2D* DyingLeft1 = getObject("DyingLeft1");    
    if (DyingLeft1) DyingLeft1->update(tDelta);

    GameObject2D* DyingLeft2 = getObject("DyingLeft2");
    if (DyingLeft2) DyingLeft2->update(tDelta);

    GameObject2D* DyingLeft3 = getObject("DyingLeft3");
    if (DyingLeft3) DyingLeft3->update(tDelta);

    GameObject2D* DyingRight1 = getObject("DyingRight1");
    if (DyingRight1) DyingRight1->update(tDelta);

    GameObject2D* DyingRight2 = getObject("DyingRight2");
    if (DyingRight2) DyingRight2->update(tDelta);

    GameObject2D* DyingRight3 = getObject("DyingRight3");
    if (DyingRight3) DyingRight3->update(tDelta);

    GameObject2D* Life1 = getObject("Life1");
    if (Life1) Life1->update(tDelta);

    GameObject2D* Life2 = getObject("Life2");
    if (Life2) Life2->update(tDelta);

    GameObject2D* Life3 = getObject("Life3");
    if (Life3) Life3->update(tDelta);

    GameObject2D* player = getObject("player");
    if (player) player->update(tDelta);

    GameObject2D* enemy1 = getObject("enemy1");
    if (enemy1) enemy1->update(tDelta);
    GameObject2D* enemy2 = getObject("enemy2");
    if (enemy2) enemy2->update(tDelta);
    GameObject2D* enemy3 = getObject("enemy3");
    if (enemy3) enemy3->update(tDelta);

    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]) bullets[i]->update(tDelta);
    }
   
    bool life1a = (getObject("Life1") != nullptr);
    bool life2a = (getObject("Life2") != nullptr);
    bool life3a = (getObject("Life3") != nullptr);

    if (!life1a && !life2a && !life3a) {
        currentGameState = GameState::GAME_OVER;
    }
    for (Enemy* e : enemies) {
        if (e) {
            e->update(tDelta);
            if (!e->alive) {
                e->respawn();
            }
        }
    }

}
std::mt19937& getRandomEngine() {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    return engine;
}
float randomPositionX()
{
    float planeWidth = getViewplaneWidth();
    float halfWidth = planeWidth / 2.0f;

    std::uniform_real_distribution<float> distribution(-halfWidth, halfWidth);
    
    return distribution(getRandomEngine());
}
float randomPositionY()
{
    float planeHeight = getViewplaneHeight();
    float halfHeight = planeHeight / 2.0f;

    // Top 10% starts at 90% of the positive range so that the enemys spawn near the top
    float startY = halfHeight * 0.90f;
    float endY = halfHeight;

    std::uniform_real_distribution<float> distribution(startY, endY);

    return distribution(getRandomEngine());
}
float randomRotation()
{
    std::uniform_real_distribution<float> distribution(0.0f, 360.0f);

    return distribution(getRandomEngine());
}

float randomSizeX()
{
    std::uniform_real_distribution<float> distribution(0.3, 1.5);

    return distribution(getRandomEngine());
}
float randomSizeY()
{
    std::uniform_real_distribution<float> distribution(0.3, 1.5);

    return distribution(getRandomEngine());
}
GLuint randomEnemyTexture()
{
    

    std::uniform_int_distribution<int> distribution(0, 2);

    float engine = distribution(getRandomEngine());

    if (engine == 0)
    {
        return loadTexture("Resources\\Textures\\asteroid1.png");
    }
    else if (engine == 1)
    {
        return  loadTexture("Resources\\Textures\\asteroid2.png");
    }
    else if (engine == 2)
    {
         return loadTexture("Resources\\Textures\\asteroid3.png");
    }
    else
    {
        return 0;
    }

    
}


void myRender(GLFWwindow* window) {

    // Clear with black (engine background may vary)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup projection to match engine's viewplane
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-getViewplaneWidth() / 2.0f, getViewplaneWidth() / 2.0f, -getViewplaneHeight() / 2.0f, getViewplaneHeight() / 2.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render axis lines if engine shows them
    if (axisLinesVisible()) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, -getViewplaneHeight());
        glVertex2f(0.0f, getViewplaneHeight());
        glVertex2f(-getViewplaneWidth(), 0.0f);
        glVertex2f(getViewplaneWidth(), 0.0f);
        glEnd();
    }

    
   

    // Draw UI overlay based on game state
    if (currentGameState == GameState::MAIN_MENU) {
        // background objects already initialized once at startup
		player->velocity = glm::vec3(2.0f, -1.0f, 0.0f);
		glBuildFontFromFile(L"Resources\\Font\\Skytone.otf", L"Skytone", 64);
        renderBackgroundObjects();
        glRasterPos2f(-getViewplaneWidth()/5.5f, -getViewplaneHeight() / -5.5f);
        glPrint("Asteroids");

        // render buttons
        if (playButton) playButton->render();
        if (exitButton) exitButton->render();
        glDeleteFont();
        
    }
	else if (currentGameState == GameState::PLAYERVELOCITYRESET) {
        
        
            player->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        
     
        currentGameState = GameState::PLAYING;
    }
    else if (currentGameState == GameState::PLAYING) {
        // show lives or simple HUD
       
        glBuildFont();
        renderObjects();
        
        
        char buf[64];
        sprintf_s(buf, "%d", Bullets::points);
        glRasterPos2f(0.0f, getViewplaneHeight()-5.5f);
        glPrint(buf);
        glDeleteFont();
		
    }
    else if (currentGameState == GameState::GAME_OVER)
    {
        player->velocity = glm::vec3(2.0f, -1.0f, 0.0f);
        glBuildFont();
        renderBackgroundObjects();
        char buf[64];
        sprintf_s(buf, "Score: %d", Bullets::points);
        glRasterPos2f(-1.3f, 0.5f);
        glPrint(buf);
        glDeleteFont();
        glBuildFontFromFile(L"Resources\\Font\\Another Danger Slanted - Demo.otf", L"Another Danger Slanted - Demo", 48);
        glRasterPos2f(-1.5f, 2.0f);
        glPrint("GAME OVER");
        glRasterPos2f(-2.2f, -1.0f);
        glPrint("Press ESC to Exit");
        glDeleteFont();
    }

}

void myMouseButtonHandler(GLFWwindow* window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS) return;

    // get cursor position in window pixels
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    // convert to viewplane coordinates
    int ww, wh;
    glfwGetWindowSize(window, &ww, &wh);

    float vx = (float)x / (float)ww * getViewplaneWidth() - getViewplaneWidth() / 2.0f;
    // note: GLFW y=0 is top of window, viewplane y=+ is up, so invert
    float vy = (1.0f - (float)y / (float)wh) * getViewplaneHeight() - getViewplaneHeight() / 2.0f;

    glm::vec2 clickPos(vx, vy);

    if (currentGameState == GameState::MAIN_MENU) {
        if (playButton && playButton->containsPoint(clickPos)) {
            currentGameState = GameState::PLAYERVELOCITYRESET;
            deleteObject("menuPlay");
            deleteObject("menuExit");
            return;
        }
        if (exitButton && exitButton->containsPoint(clickPos)) {
            glfwSetWindowShouldClose(window, true);
            return;
        }
    }
}
