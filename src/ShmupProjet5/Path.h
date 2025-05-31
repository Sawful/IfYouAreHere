#pragma once
#include "SFML/Graphics.hpp"

class Entity;

struct Path
{
    float mCompletion;
    float mCompleteTime;

    Path(float completeTime);
	virtual bool FollowPath(float deltaTime, Entity* entity);
    virtual bool LerpFollowPath(float deltaTime, Entity* entity);
    void ResetCompletion();
};

struct PointPath : public Path
{
    sf::Vector2f mCoordinates;

    PointPath(sf::Vector2f coordinates, float completeTime);

    virtual bool FollowPath(float deltaTime, Entity* entity) override;
};

struct LinePath : public Path
{
    sf::Vector2f mP1;
    sf::Vector2f mP2;

    LinePath(sf::Vector2f p1, sf::Vector2f p2, float completeTime);

    virtual bool FollowPath(float deltaTime, Entity* entity) override;
};

struct BezierCurvePath : public Path
{
    sf::Vector2f mP1;
    sf::Vector2f mP2;
    sf::Vector2f mP3;
    sf::Vector2f mP4;

    BezierCurvePath(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, float completeTime);

    virtual bool FollowPath(float deltaTime, Entity* entity) override;
};