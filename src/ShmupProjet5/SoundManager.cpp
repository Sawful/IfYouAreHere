#include "SoundManager.h"

SoundManager::SoundManager()
{
	mHitSoundBuffer.loadFromFile("..\\..\\..\\res\\hitsound.mp3");
	mHitSound.setBuffer(mHitSoundBuffer);
	mHitSound.setVolume(70);

	mPickupSoundBuffer.loadFromFile("..\\..\\..\\res\\pickup.mp3");
	mPickupSound.setBuffer(mPickupSoundBuffer);
	mPickupSound.setVolume(70);

	mWeaponUpSoundBuffer.loadFromFile("..\\..\\..\\res\\weaponup.mp3");
	mWeaponUpSound.setBuffer(mWeaponUpSoundBuffer);
	mWeaponUpSound.setVolume(70);

	mEnemyDeathSoundBuffer.loadFromFile("..\\..\\..\\res\\enemydeath.mp3");
	mEnemyDeathSound.setBuffer(mEnemyDeathSoundBuffer);
	mEnemyDeathSound.setVolume(50);

	mStage1.openFromFile("..\\..\\..\\res\\FungalDream.mp3");
	mStage1.setVolume(10);
	mStage1Boss.openFromFile("..\\..\\..\\res\\touhoulike2.mp3");
	mStage1Boss.setVolume(20);

	mStage2Boss.openFromFile("..\\..\\..\\res\\parhelion.mp3");
	mStage2Boss.setVolume(20);
}

SoundManager::~SoundManager()
{
	mHitSound.stop();
	mPickupSound.stop();
	mWeaponUpSound.stop();
	mEnemyDeathSound.stop();
	mStage1.stop();
	mStage1Boss.stop();
	mStage2Boss.stop();
}

void SoundManager::PlaySound(SoundType sound)
{
	switch(sound)
	{
	case HITSOUND:
		mHitSound.play();
		break;
	case ENEMYDEATHSOUND:
		mEnemyDeathSound.play();
		break;
	case WEAPONUPSOUND:
		mWeaponUpSound.play();
		break;
	case PICKUPSOUND:
		mPickupSound.play();
		break;
	}
}

void SoundManager::ChangeMusic(MusicType newMusic)
{
	if (mCurrentMusic != nullptr)
	{
		mCurrentMusic->stop();
	}

	switch (newMusic)
	{
	case STAGE1:
		mCurrentMusic = &mStage1;
		break;

	case STAGE1BOSS:
		mCurrentMusic = &mStage1Boss;
		break;

	case STAGE2BOSS:
		mCurrentMusic = &mStage2Boss;
		break;
	}

	mCurrentMusic->play();
}


