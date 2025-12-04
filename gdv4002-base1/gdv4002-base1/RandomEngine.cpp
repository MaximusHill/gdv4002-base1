#include "RandomEngine.h"
#include "Engine.h"
#include <random>





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
        return loadTexture("Resources\\Textures\\AsteroidUpdated1.png");
    }
    else if (engine == 1)
    {
        return  loadTexture("Resources\\Textures\\AsteroidUpdated2.png");
    }
    else if (engine == 2)
    {
        return loadTexture("Resources\\Textures\\AsteroidUpdated3.png");
    }
    else
    {
        return 0;
    }


}