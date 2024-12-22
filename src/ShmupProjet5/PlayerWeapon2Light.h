#pragma once
#include "PlayerWeapon.h"


class PlayerWeapon2Light: public PlayerWeapon
{

public:
	PlayerWeapon2Light(Character* owner);
	virtual void Shoot();

};

