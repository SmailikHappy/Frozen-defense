#pragma once

//---------------------------------------//
// Subclass of tower / unique tower type //
//---------------------------------------//

#ifndef ICE_TOWER_H
#define ICE_TOWER_H

#include "tower.h"

class IceTower : public Tower
{
public:
	float futureSpeedKoef;

	void LvlUp();		// upgrade function

	void Shoot(vector<Enemy*> triggeredEnemies);

	IceTower(int x, int y, Tmpl8::Sprite* sprite, float radius, float damage, int lvlUpCost, float cooldown, int sellCost);
};

#endif // ! FLAME_TOWER_H