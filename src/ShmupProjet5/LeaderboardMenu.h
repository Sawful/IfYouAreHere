#pragma once
#include "Scene.h"
#include "MenuButton.h"
#include <iostream>
#include <fstream>


struct ScoreLine
{
	int score;
	char name[4];
};

class LeaderboardMenu: public Scene
{
	std::vector<MenuButton*> mLeaderboardButtons;
	sf::Texture mButtonTexture;
	sf::Texture mButtonTextureHovered;
	sf::Texture background;
	sf::Font mLeaderboardFont;

	sf::Sprite leadBackground;

	sf::View mLeaderboardView;

	std::vector<sf::Text> mLeaderboardScore;
	std::vector <std::string> mLeaderboardScoreText;

	float mButtonSwapTime = 0.0f;
	float mButtonSwapCooldown = 0.2f;

	float mButtonConfirmTime = 0.0f;
	float mButtonConfirmCooldown = 0.5f;

	std::fstream mScoreFile;

	std::vector<ScoreLine> mHighscore;

	int mButtonHovered;

public:
	LeaderboardMenu(sf::RenderWindow* window);
	virtual void Update(float deltaTime) override;
	void AddButton(MenuButton* button);
	virtual void EnterScene();
	virtual void Draw() override;
	virtual void ResetScene();
	void GetPreviousScore();
	void SaveScore();
	void GetHighscore();
};

