#pragma once
#include "PlayerWeapon.h"


class PlayerWeapon2Dark : public PlayerWeapon
{

public:
	PlayerWeapon2Dark(Character* owner);
	virtual void Shoot();
};
