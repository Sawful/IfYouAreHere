#include "main.h"
#include "EnemyTest.h"
#include "SceneManager.h"
#include "Stage1.h"
#include "ExtraStage.h"
#include "GameManager.h"
#include "SFML/Graphics.hpp"


int main()
{
	srand(time(nullptr));

	GameManager* gm = GameManager::GetInstance();

	gm->Initialize();
	//e
	gm->Run();
}
