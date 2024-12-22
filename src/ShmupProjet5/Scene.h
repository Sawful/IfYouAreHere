#pragma once
#include "Entity.h"


class Scene
{
protected:
	std::vector<Entity*> entities;
	sf::RenderWindow* mCurrentWindow;

public:
	Scene(sf::RenderWindow* window);
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void AddToEntities(Entity* entity);
	virtual void EnterScene() = 0;
	virtual void ResetScene() = 0;
	
};

