#pragma once
#include "PlayerWeapon.h"

class PlayerWeapon3BLight : public PlayerWeapon
{
public:
	PlayerWeapon3BLight(Character* owner);
	virtual void Shoot();
};

