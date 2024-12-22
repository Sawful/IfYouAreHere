#include "PlayerController.h"
#include "GameManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"


PlayerController::PlayerController(TextureName pcTexture, GameManager* gm): Entity(sf::Vector2f(0.0f, 0.0f), 0.0f, pcTexture, true)
{
    mGameManager = gm;    
    
    mPlayerTexture = *(gm->GetResourceManager()->GetTexture(LIGHT_KITTY_TEXTURE));
    mPlayerAlterTexture = *(gm->GetResourceManager()->GetTexture(DARK_KITTY_TEXTURE));

    mPlayer = new Player(sf::Vector2f(0.0f, 0.0f), 0.0f, LIGHT_KITTY_TEXTURE, true, this);
    mPlayerAlter = new Player(sf::Vector2f(0.0f, 0.0f), 0.0f, DARK_KITTY_TEXTURE, false, this);

    mPlayerWeapon1Dark = new PlayerWeapon1Dark(mPlayerAlter);
    mPlayerWeapon2Dark = new PlayerWeapon2Dark(mPlayerAlter);
    mPlayerWeapon3ADark = new PlayerWeapon3ADark(mPlayerAlter);
    mPlayerWeapon3BDark = new PlayerWeapon3BDark(mPlayerAlter);
    mPlayerWeapon4ADark = new PlayerWeapon4ADark(mPlayerAlter);
    mPlayerWeapon4BDark = new PlayerWeapon4BDark(mPlayerAlter);

    mPlayerWeapon1Light = new PlayerWeapon1Light(mPlayer);
    mPlayerWeapon2Light = new PlayerWeapon2Light(mPlayer);
    mPlayerWeapon3ALight = new PlayerWeapon3ALight(mPlayer);
    mPlayerWeapon3BLight = new PlayerWeapon3BLight(mPlayer);
    mPlayerWeapon4ALight = new PlayerWeapon4ALight(mPlayer);
    mPlayerWeapon4BLight = new PlayerWeapon4BLight(mPlayer);

    mLightWeaponIsA = true;
    mDarkWeaponIsA = true;

    Reset();
}


void PlayerController::Update(float deltaTime)
{
    mSwapTimer -= deltaTime;
    mInvincibilityTimer -= deltaTime;

    mPlayer->SetFocusSpeed(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
    mPlayerAlter->SetFocusSpeed(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));

    mActivePlayer->UpdateTexture(0);
    mInactivePlayer->UpdateTexture(0);

    // Get Player Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        mActivePlayer->Move(deltaTime, sf::Vector2f(-1.0f, 0.0f));
        mActivePlayer->UpdateTexture(1);

        mInactivePlayer->Move(deltaTime, sf::Vector2f(1.0f, 0.0f));
        mInactivePlayer->UpdateTexture(2);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        mActivePlayer->Move(deltaTime, sf::Vector2f(1.0f, 0.0f));
        mActivePlayer->UpdateTexture(2);

        mInactivePlayer->Move(deltaTime, sf::Vector2f(-1.0f, 0.0f));
        mInactivePlayer->UpdateTexture(1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        mActivePlayer->Move(deltaTime, sf::Vector2f(0.0f, -1.0f));
        mActivePlayer->UpdateTexture(4);

        mInactivePlayer->Move(deltaTime, sf::Vector2f(0.0f, 1.0f));
        mInactivePlayer->UpdateTexture(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        mActivePlayer->Move(deltaTime, sf::Vector2f(0.0f, 1.0f));
        mActivePlayer->UpdateTexture(3);

        mInactivePlayer->Move(deltaTime, sf::Vector2f(0.0f, -1.0f));
        mInactivePlayer->UpdateTexture(4);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        // w key is pressed: the active character shoots bullets
        mActivePlayer->Shoot(deltaTime);
    }
}

void PlayerController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw nothing because player controller does not need to be drawn
}

Player* PlayerController::GetActivePlayerPointer()
{
    return mActivePlayer;
}

sf::Vector2f PlayerController::GetActivePlayerPosition()
{
    return mActivePlayer->getPosition();
}

std::vector<Player*> PlayerController::GetPlayers()
{
    return std::vector<Player*>({mPlayer, mPlayerAlter});
}

void PlayerController::ChangeStage()
{
    Level* newStage = mGameManager->GetSceneManager()->GetCurrentStage();

    mPlayerWeapon1Light->SetCurrentStage(newStage);
    mPlayerWeapon2Light->SetCurrentStage(newStage);
    mPlayerWeapon3ALight->SetCurrentStage(newStage);
    mPlayerWeapon3BLight->SetCurrentStage(newStage);
    mPlayerWeapon4ALight->SetCurrentStage(newStage);
    mPlayerWeapon4BLight->SetCurrentStage(newStage);

    mPlayerWeapon1Dark->SetCurrentStage(newStage);
    mPlayerWeapon2Dark->SetCurrentStage(newStage);
    mPlayerWeapon3ADark->SetCurrentStage(newStage);
    mPlayerWeapon4ADark->SetCurrentStage(newStage);
    mPlayerWeapon3BDark->SetCurrentStage(newStage);
    mPlayerWeapon4BDark->SetCurrentStage(newStage);
}

void PlayerController::SetLightWeapon(bool lightIsA)
{
    mLightWeaponIsA = lightIsA;
}

void PlayerController::SetDarkWeapon(bool darkIsA)
{
    mDarkWeaponIsA = darkIsA;
}

void PlayerController::IncreaseWeaponPower(int amount)
{
    mWeaponPower += amount;

    if (mSoundManager == nullptr)
    {
        mSoundManager = mGameManager->GetSoundManager();
    }

    mSoundManager->PlaySound(PICKUPSOUND);

    // Check if new weapons have to be added
    switch (mWeaponPower)
    {
    case 8:
        mPlayer->AddWeapon(mPlayerWeapon2Light);
        mPlayerAlter->AddWeapon(mPlayerWeapon2Dark);

        mSoundManager->PlaySound(WEAPONUPSOUND);
        break;

    case 16:
        if(mLightWeaponIsA)
        {
            mPlayer->AddWeapon(mPlayerWeapon3ALight);
        }
        else
        {
            mPlayer->AddWeapon(mPlayerWeapon3BLight);
        }

        if (mDarkWeaponIsA)
        {
            mPlayerAlter->AddWeapon(mPlayerWeapon3ADark);
        }
        else
        {
            mPlayerAlter->AddWeapon(mPlayerWeapon3BDark);
        }

        mSoundManager->PlaySound(WEAPONUPSOUND);
        break;

    case 32:
        if (mLightWeaponIsA)
        {
            mPlayer->AddWeapon(mPlayerWeapon4ALight);
        }
        else
        {
            mPlayer->AddWeapon(mPlayerWeapon4BLight);
        }

        if (mDarkWeaponIsA)
        {
            mPlayerAlter->AddWeapon(mPlayerWeapon4ADark);
        }
        else
        {
            mPlayerAlter->AddWeapon(mPlayerWeapon4BDark);
        }

        mSoundManager->PlaySound(WEAPONUPSOUND);
        break;
    }
}

bool PlayerController::IsInvincible()
{
    return mInvincibilityTimer > 0.0f;
}

void PlayerController::SetInvincible()
{
    mInvincibilityTimer = mInvincibilityCooldown;
}

void PlayerController::TakeDamage()
{
    // Hit stop
    mGameManager->SetPause(true);

    SetInvincible();

    if (DecreaseLife())
    {
        mGameManager->GetSceneManager()->ChangeToLeaderboard();
    }
}

void PlayerController::Reset()
{
    mPlayer->ClearWeapons();
    mPlayerAlter->ClearWeapons();

    mWeaponPower = 0;

    mPlayer->AddWeapon(mPlayerWeapon1Light);
    mPlayerAlter->AddWeapon(mPlayerWeapon1Dark);

    mActivePlayer = mPlayer;
    mInactivePlayer = mPlayerAlter;

    mLives = 3;

    mPlayer->SetEntityActive(true);
    mPlayerAlter->SetEntityActive(true);
}

bool PlayerController::DecreaseLife()
{
    return (--mLives <= 0);
}

void PlayerController::Swap()
{
    if (mSwapTimer > 0.0f)
    {
        return;
    }

    mSwapTimer = mSwapCooldown;

    Player* temp = mInactivePlayer;

    mInactivePlayer = mActivePlayer;
    mActivePlayer = temp;

    mActivePlayer->SetCurrentPlayer(true);
    mInactivePlayer->SetCurrentPlayer(false);

    mActivePlayer->UpdateTexture();
    mInactivePlayer->UpdateTexture();
}

void PlayerController::SetGameScreen(sf::FloatRect newSize)
{
    mActivePlayer->SetGameScreen(newSize);
    mInactivePlayer->SetGameScreen(newSize);
}

sf::FloatRect PlayerController::GetGameScreen()
{
    return mActivePlayer->GetGameScreen();
}

int PlayerController::GetLives() {
    return mLives;
}
