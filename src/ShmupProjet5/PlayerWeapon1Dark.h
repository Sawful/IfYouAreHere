#pragma once
#include "PlayerWeapon.h"
#include "BulletBase.h"


class PlayerWeapon1Dark : public PlayerWeapon
{

public:
	PlayerWeapon1Dark(Character* owner);
	virtual void Shoot();
};

