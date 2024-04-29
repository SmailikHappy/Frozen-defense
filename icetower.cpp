#include "icetower.h"

IceTower::IceTower(int x, int y, Tmpl8::Sprite* sprite, float radius, float damage, int lvlUpCost, float cooldown, int sellCost)
{
	isActive = true;
	this->sprite = sprite;
	this->position = { (float) x + sprite->GetWidth() / 2, (float) y + sprite->GetHeight() / 2 };
	this->sprRenderPosX = x;
	this->sprRenderPosY = y;
	this->radius = radius * cellEdge;
	this->damage = damage;
	this->towerelement = Element::ice;
	color = iceColor;
	this->lvlUpCost = lvlUpCost;
	this->cooldown = cooldown * 1000.0f;
	this->sellCost = sellCost;

	this->futureSpeedKoef = iceFutureSpeedKoef;
}

void IceTower::LvlUp()
{
	damage += additionalIceDmg;
	lvl++;
	radius += additionalIceRad * cellEdge;
	sellCost += lvlUpCost - additionalIceLvlUpCost;
	lvlUpCost += additionalIceLvlUpCost;
	cooldown += additionalIceCoolDown;
	futureSpeedKoef += additionalIceFutureSpeedKoef;
}

void IceTower::Shoot(vector<Enemy*> triggeredEnemies) {
	for (Enemy* enemy : triggeredEnemies)
	{
		enemy->speedKoef *= futureSpeedKoef;
	}
}