#pragma once
#include "PlayerWeapon.h"
#include "BulletBase.h"


class PlayerWeapon1Light: public PlayerWeapon
{

public:
	PlayerWeapon1Light(Character* owner);
	virtual void Shoot();

};

