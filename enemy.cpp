#include "enemy.h"


Enemy::Enemy(EnemysType* type, int k)
{
	this->sprite = type->sprite;
	this->rewardprice = type->rewardPrice + type->rewardForKoef * (k - 1);
	this->speed = type->speed;
	this->hp = type->hp + (float) type->hpKoef * (k - 1);
	this->castledamage = type->castleDMG;
	this->directionX = 1;
	this->directionY = 0;
	this->resistance = type->resistance;
	this->position = spawnEnemyPos;
	this->isAlive = true;

	this->healthBar.SetMaxHealth(hp);
}

Enemy::Enemy() {}

void Enemy::Render()
{
	sprite->Draw(screen_, (int) position.x - this->sprite->GetWidth() / 2, (int) position.y - this->sprite->GetHeight() / 2);
	healthBar.Render(position);
}

void Enemy::Damage(float dmg)
{
	if (dmg >= hp) {	// if damage will not kill
		doneDamage += hp;
		isAlive = false;
		ChangeMainInfo(&gold, rewardprice);
	}
	else {				// if damage is critical
		doneDamage += dmg;
		hp -= dmg;
		healthBar.Update(hp);
	}
}
