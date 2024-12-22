#include "Character.h"
#include "Bullet.h"
#include "Drop.h"


Character::Character(sf::Vector2f position, float rotation, TextureName texture, Tag hitboxTag, bool isActive):
	Entity(position, rotation, texture, isActive),
	mHitbox(hitboxTag)
{
}

void Character::CheckCollisions(std::vector<Bullet*>* bullets)
{
	mHitbox.SetPosition(getPosition());

	for (Bullet* bullet : *bullets)
	{
		if (!bullet->IsEntityActive())
		{
			continue;
		}

		if (mHitbox.IsColliding(bullet->GetHitboxPointer()))
		{
			// Instead, call an "on hit" method
			bullet->OnHit(this);
			// bullet->SetEntityActive(false);

			return;
		}
	}
}
