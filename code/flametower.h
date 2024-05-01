#pragma once

//---------------------------------------//
// Subclass of tower / unique tower type //
//---------------------------------------//

#ifndef FLAME_TOWER_H
#define FLAME_TOWER_H

#include "tower.h"

class FlameTower : public Tower
{
public:
	void Shoot(vector<Enemy*> triggeredEnemies);

	void LvlUp();		// upgrade function

	using Tower::Tower;
};

#endif // ! FLAME_TOWER_H