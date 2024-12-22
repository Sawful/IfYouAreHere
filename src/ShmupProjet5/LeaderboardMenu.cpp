#include "LeaderboardMenu.h"
#include "GameManager.h"
#include "SceneManager.h"
#include <string>


LeaderboardMenu::LeaderboardMenu(sf::RenderWindow* window) : Scene(window)
{
	
}

void LeaderboardMenu::Initialize()
{
	mLeaderboardFont.loadFromFile("../../../res/Gobold Regular.otf");

	mLeaderboardBackground.setTexture(background);
	mLeaderboardBackground.setScale(sf::Vector2f(2, 2));

	mLeaderboardView = sf::View(sf::FloatRect(0, 0, 1200, 900));

	mButtonHovered = 0;

	AddButton(new MenuButton(sf::Vector2f(950.0f, 600.0f), 0.0f, sf::Vector2f(200.0f, 80.0f), BUTTON_TEXTURE, BUTTON_HOVERED_TEXTURE));
	AddButton(new MenuButton(sf::Vector2f(950.0f, 700.0f), 0.0f, sf::Vector2f(200.0f, 80.0f), BUTTON_TEXTURE, BUTTON_HOVERED_TEXTURE));

	mLeaderboardButtons[0]->SetHover(true);
}

void LeaderboardMenu::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	mButtonSwapTime -= deltaTime;
	mButtonConfirmTime -= deltaTime;

	if (mButtonSwapTime > 0.0f)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (mButtonHovered - 1 < 0)
		{
			return;
		}

		mButtonSwapTime = mButtonSwapCooldown;

		mLeaderboardButtons[mButtonHovered]->SetHover(false);

		--mButtonHovered;

		mLeaderboardButtons[mButtonHovered]->SetHover(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (mButtonHovered + 1 > 1)
		{
			return;
		}

		mButtonSwapTime = mButtonSwapCooldown;

		mLeaderboardButtons[mButtonHovered]->SetHover(false);

		++mButtonHovered;

		mLeaderboardButtons[mButtonHovered]->SetHover(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (mButtonConfirmTime > 0.0f)
		{
			return;
		}

		mButtonConfirmTime = mButtonConfirmCooldown;

		if (mButtonHovered == 0)
		{
			SaveScore();
			GameManager::GetInstance()->GetSceneManager()->ChangeToMainMenu();
		}
		if (mButtonHovered == 1)
		{
			GameManager::GetInstance()->GetSceneManager()->ChangeToMainMenu();
		}
	}
}

void LeaderboardMenu::AddButton(MenuButton* button)
{
	mLeaderboardButtons.push_back(button);
	entities.push_back(button);
}

void LeaderboardMenu::EnterScene()
{
	mButtonConfirmTime = mButtonConfirmCooldown;

	mCurrentWindow->setView(mLeaderboardView);

	GetPreviousScore();

	GetHighscore();
}

void LeaderboardMenu::Draw()
{
	mCurrentWindow->draw(mLeaderboardBackground);

	Scene::Draw();

	for (int i = 0; i < mLeaderboardScore.size(); i++)
	{
		mCurrentWindow->draw(mLeaderboardScore[i]);
	}
}

void LeaderboardMenu::ResetScene()
{
	mLeaderboardScore.clear();
	mLeaderboardScoreText.clear();
	mHighscore.clear();
	mButtonHovered = 0;
	mLeaderboardButtons[0]->SetHover(true);
	mButtonConfirmTime = mButtonConfirmCooldown;
}

void LeaderboardMenu::GetPreviousScore()
{
	mScoreFile.open("..\\..\\..\\res\\Leaderboard.txt");

	std::string scoreLine;

	int i = 0;
	ScoreLine line;
	while (std::getline(mScoreFile, scoreLine))
	{
		if (i == 0)
		{
			line = ScoreLine();
			line.score = std::stoi(scoreLine);
			i++;
		}

		else
		{
			for (int j = 0; j < 3; j++)
			{
				line.name[j] = scoreLine[j];
			}
			mHighscore.push_back(line);
			i = 0;
		}
	}

	mScoreFile.close();

	line = ScoreLine();

	GameManager* gm = GameManager::GetInstance();

	line.score = gm->GetScore();
	strcpy_s(line.name, "> "); //here was name
	mHighscore.push_back(line);

	gm->ResetScore();
}

void LeaderboardMenu::SaveScore()
{
	mScoreFile.open("..\\..\\..\\res\\Leaderboard.txt", std::ios::app);

	// Last entry is most recent score
	mScoreFile << mHighscore[mHighscore.size() - 1].score << "\n" << mHighscore[mHighscore.size() - 1].name << "\n";

	mScoreFile.close();
}

// Comparator function
bool comp(ScoreLine a, ScoreLine b) {
	return a.score > b.score;
}

void LeaderboardMenu::GetHighscore()
{
	sort(mHighscore.begin(), mHighscore.end(), comp);

	for (int i = 0; i < 10; i++)
	{
		mLeaderboardScore.push_back(sf::Text());
	}

	int scoresAmountMin = mHighscore.size() > 10 ? 10 : mHighscore.size();

	for (int i = 0; i < scoresAmountMin; i++)
	{
		std::cout << mHighscore[i].name << mHighscore[i].score;

		std::string line = "> " + std::to_string(mHighscore[i].score);

		mLeaderboardScoreText.push_back(line);
		mLeaderboardScore[i].setFont(mLeaderboardFont);
		mLeaderboardScore[i].setString(mLeaderboardScoreText[i]);
		mLeaderboardScore[i].setPosition(sf::Vector2f(500.0f, 100.0f + (100.0f * i)));
	}

}
