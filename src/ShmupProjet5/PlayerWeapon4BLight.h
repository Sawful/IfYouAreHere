#pragma once
#include "PlayerWeapon.h"

class PlayerWeapon4BLight : public PlayerWeapon
{
public:
	PlayerWeapon4BLight(Character* owner);
	virtual void Shoot();
};

