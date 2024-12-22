#include "main.h"
#include "EnemyTest.h"
#include "SceneManager.h"
#include "Stage1.h"
#include "Stage2.h"
#include "GameManager.h"
#include "SFML/Graphics.hpp"


int main()
{
	srand(time(nullptr));

	GameManager* gm = GameManager::GetInstance();
	sf::RenderWindow* window = gm->GetWindow();
	SceneManager* sm = gm->GetSceneManager();
	PlayerController* pc = sm->GetPlayerController();
	//e

	sf::RectangleShape* sceneSwapOverlay = sm->GetSceneOverlay();

	sf::Clock clock;
	float deltaTime;

	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		if (gm->GetPause())
		{
			// Until unpaused, no logic runs, and nothing is drawn.
			if (gm->HasPauseTimeEnded())
			{
				gm->SetPause(false);
			}

			continue;
		}

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				delete gm->GetSoundManager();

				window->close();
			}

			if (event.KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					pc->Swap();
				}
			}
		}
		
		sm->GetCurrentScene()->Update(deltaTime);

		window->clear(sf::Color::Black);

		sm->GetCurrentScene()->Draw();
		sm->UpdateSceneTransition(deltaTime);
		window->draw(*sceneSwapOverlay);

		window->display();

	}

	return 0;
}
