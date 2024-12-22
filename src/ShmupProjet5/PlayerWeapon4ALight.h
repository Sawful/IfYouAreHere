#pragma once
#include "PlayerWeapon.h"
class PlayerWeapon4ALight : public PlayerWeapon
{

public:
	PlayerWeapon4ALight(Character* owner);
	virtual void Shoot();
};

