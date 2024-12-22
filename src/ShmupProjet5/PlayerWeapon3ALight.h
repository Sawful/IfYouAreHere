#pragma once
#include "PlayerWeapon.h"


class PlayerWeapon3ALight : public PlayerWeapon
{

public:
	PlayerWeapon3ALight(Character* owner);
	virtual void Shoot();
};

