#include "stonetower.h"

Tmpl8::Sprite bulletSpr(new Tmpl8::Surface("assets/playzone/bullets/stoneBullet.png"), 1);
vector<StoneBullet*> stoneBullets;

void StoneTower::Shoot(vector<Enemy*> triggeredEnemies)
{
	StoneBullet* bullet = new StoneBullet(position, triggeredEnemies[0], damage);
	stoneBullets.push_back(bullet);
}

void StoneTower::LvlUp()
{
	damage += additionalStoneDmg;
	lvl++;
	radius += additionalStoneRad * cellEdge;
	sellCost += lvlUpCost - additionalStoneLvlUpCost;
	lvlUpCost += additionalStoneLvlUpCost;
	cooldown += additionalStoneCoolDown;
}

StoneBullet::StoneBullet(Tmpl8::vec2 spawnPos, Enemy* target, float dmg):
	position(spawnPos),
	target(target),
	sprite(&bulletSpr),
	dmg(dmg)
	{}

void StoneBullet::Hit()
{
	target->Damage(dmg);
}

void StoneBullet::Render()
{
	sprite->Draw(screen_, (int) position.x - sprite->GetWidth() / 2, (int) position.y - sprite->GetHeight() / 2);
}