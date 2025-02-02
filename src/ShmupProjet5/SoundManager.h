#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>


enum SoundType
{
	HITSOUND,
	WEAPONUPSOUND,
	ENEMYDEATHSOUND,
	PICKUPSOUND
};

enum MusicType
{
	STAGE1,
	STAGE1BOSS,
	STAGE2BOSS
};

class SoundManager
{
	sf::Music* mCurrentMusic;

	std::unordered_map<SoundType, std::pair<sf::Sound, sf::SoundBuffer>> mSounds;
	std::unordered_map<MusicType, sf::Music> mMusics;

public:
	SoundManager();
	~SoundManager();

	void PlaySound(SoundType sound);
	void ChangeMusic(MusicType newMusic);
};

