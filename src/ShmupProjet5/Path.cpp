#include "Path.h"
#include "Entity.h"
#include "cmath"

PointPath::PointPath(sf::Vector2f coordinates, float completeTime) : Path(completeTime)
{
	mCoordinates = coordinates;
}

bool PointPath::FollowPath(float deltaTime, Entity* entity)
{
    entity->setPosition(mCoordinates);
    Path::FollowPath(deltaTime, entity);

    return (mCompletion >= 1.0f);
}

LinePath::LinePath(sf::Vector2f p1, sf::Vector2f p2, float completeTime) : Path(completeTime)
{
    mP1 = p1;
    mP2 = p2;
}

bool LinePath::FollowPath(float deltaTime, Entity* entity)
{
    entity->setPosition(mP1 + mP2 * mCompletion);

    Path::FollowPath(deltaTime, entity);
    return (mCompletion >= 1.0f);
}

BezierCurvePath::BezierCurvePath(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, float completeTime): Path(completeTime)
{
    mP1 = p1;
    mP2 = p2;
    mP3 = p3;
    mP4 = p4;
}

bool BezierCurvePath::FollowPath(float deltaTime, Entity* entity)
{ 
    sf::Vector2f position = 
        powf(1 - mCompletion, 3) * mP1 +
        3 * powf(1 - mCompletion, 2) * mCompletion * mP2
        + 3 * (1 - mCompletion) * powf(mCompletion, 2) * mP3
        + powf(mCompletion, 3) * mP4;

    entity->setPosition(position);

    Path::FollowPath(deltaTime, entity);
    return (mCompletion >= 1.0f);
}

Path::Path(float completeTime)
{
    mCompletion = 0;
    mCompleteTime = completeTime;
}

bool Path::FollowPath(float deltaTime, Entity* entity)
{
    mCompletion += deltaTime / mCompleteTime;
    return false;
}

bool Path::LerpFollowPath(float deltaTime, Entity* entity)
{
    float completionFactor = deltaTime / mCompleteTime;
    mCompletion += mCompletion + (1 - mCompletion) * completionFactor; // MAKE ACTUAL LERP IM TOO SLEEPY FOR THIS
    return false;
}

void Path::ResetCompletion()
{
    mCompletion = 0;
}
