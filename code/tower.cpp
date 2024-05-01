#include "tower.h"

Tower::Tower(int x, int y, Tmpl8::Sprite* sprite, Element towerelement, float radius, float damage, int lvlUpCost, float cooldown, int sellCost) :
	sprite(sprite),
	position{ (float) x + sprite->GetWidth() / 2, (float) y + sprite->GetHeight() / 2 },
	sprRenderPosX(x),
	sprRenderPosY(y),
	radius(radius * cellEdge),
	damage(damage),
	towerelement(towerelement),
	lvlUpCost(lvlUpCost),
	cooldown(cooldown * 1000.0f),
	sellCost(sellCost)
{
	switch (towerelement) {
		case Element::stone:
			color = stoneColor;
			break;
		case Element::snow:
			color = snowColor;
			break;
		case Element::ice:
			color = iceColor;
			break;
		case Element::flame:
			color = flameColor;
			break;
	}
}

Tower::Tower() { this->isActive = false; }

void Tower::LvlUp()
{}

void Tower::RenderTower()
{
	sprite->Draw(screen_, sprRenderPosX, sprRenderPosY);
}

void Tower::Shoot(vector<Enemy*> triggeredEnemies) {
	printf("tower shoots");
}