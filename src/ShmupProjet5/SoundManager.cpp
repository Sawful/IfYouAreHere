#include "SoundManager.h"

SoundManager::SoundManager()
{
	mSounds[HITSOUND].second.loadFromFile("..\\..\\..\\res\\hitsound.mp3");
	mSounds[HITSOUND].first.setBuffer(mSounds[HITSOUND].second);
	mSounds[HITSOUND].first.setVolume(70);

	mSounds[PICKUPSOUND].second.loadFromFile("..\\..\\..\\res\\pickup.mp3");
	mSounds[PICKUPSOUND].first.setBuffer(mSounds[PICKUPSOUND].second);
	mSounds[PICKUPSOUND].first.setVolume(70);

	mSounds[WEAPONUPSOUND].second.loadFromFile("..\\..\\..\\res\\weaponup.mp3");
	mSounds[WEAPONUPSOUND].first.setBuffer(mSounds[WEAPONUPSOUND].second);
	mSounds[WEAPONUPSOUND].first.setVolume(70);

	mSounds[ENEMYDEATHSOUND].second.loadFromFile("..\\..\\..\\res\\enemydeath.mp3");
	mSounds[ENEMYDEATHSOUND].first.setBuffer(mSounds[ENEMYDEATHSOUND].second);
	mSounds[ENEMYDEATHSOUND].first.setVolume(50);

	mMusics[STAGE1].openFromFile("..\\..\\..\\res\\FungalDream.mp3");
	mMusics[STAGE1].setVolume(10);

	mMusics[STAGE1BOSS].openFromFile("..\\..\\..\\res\\touhoulike2.mp3");
	mMusics[STAGE1BOSS].setVolume(20);

	mMusics[STAGE2BOSS].openFromFile("..\\..\\..\\res\\parhelion.mp3");
	mMusics[STAGE2BOSS].setVolume(20);
}

SoundManager::~SoundManager()
{
	for (auto& sounds : mSounds)
	{
		sounds.second.first.stop();
	}

	for (auto& musics : mMusics)
	{
		musics.second.stop();
	}
}

void SoundManager::PlaySound(SoundType sound)
{
	mSounds[sound].first.play();
}

void SoundManager::ChangeMusic(MusicType newMusic)
{
	if (mCurrentMusic != nullptr)
	{
		mCurrentMusic->stop();
	}

	mCurrentMusic = &mMusics[newMusic];

	mCurrentMusic->play();
}


