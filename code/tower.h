#pragma once

//----------------------//
// (parent) tower class //
//----------------------//

#ifndef TOWER_H
#define TOWER_H

#include "globalvariables.h"
#include "enemy.h"

class Tower {

public:
	// all important varaibles
	bool isActive = true;

	Tmpl8::vec2 position;
	Tmpl8::Sprite* sprite;
	int sprRenderPosX, sprRenderPosY;
	Element towerelement;
	unsigned short lvl = 1;
	float damage = 0.0f;
	float radius;
	int lvlUpCost;
	float cooldown = 0.0f;
	float timePassed = 0.0f;
	int sellCost;
	Tmpl8::Pixel color;
	// float leftBorder, rightBorder, topBorder, botBorder;


	// Constructor for Tower
	explicit Tower(
		int x,
		int y,
		Tmpl8::Sprite* sprite,
		Element towerelement,
		float radius,
		float damage,
		int lvlUpCost,
		float cooldown,
		int sellCost
	);

	Tower();

	// Tower - upgrade function
	virtual void LvlUp();									// each tower has its own variables to upgrade / sell, so it is virtual

	void RenderTower();		// render it

	virtual void Shoot(vector<Enemy*> triggeredEnemies);	// each tower has its own way to shoot
};
#endif // !TOWER_H