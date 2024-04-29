#include "flametower.h"

void FlameTower::Shoot(vector<Enemy*> triggeredEnemies) {

	// everyone involved is damaged
	for (Enemy* enemy : triggeredEnemies)
	{
		enemy->Damage(damage);
	} 
}

void FlameTower::LvlUp()
{
	damage += additionalFlameDmg;
	lvl++;
	radius += additionalFlameRad * cellEdge;
	sellCost += lvlUpCost - additionalFlameLvlUpCost;
	lvlUpCost += additionalFlameLvlUpCost;
	cooldown += additionalFlameCoolDown;
}