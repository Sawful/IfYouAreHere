#include "Scene.h"
#include "BulletSnake.h"


Scene::Scene(sf::RenderWindow* window)
{
	mCurrentWindow = window;
}

void Scene::Update(float deltaTime)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsEntityActive())
		{
			continue;
		}

		entities[i]->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsEntityActive())
		{
			continue;
		}

		mCurrentWindow->draw(*entities[i]);
	}
}

void Scene::AddToEntities(Entity* entity)
{
	entities.push_back(entity);
}
