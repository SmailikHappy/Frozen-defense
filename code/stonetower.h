#pragma once

//---------------------------------------//
// Subclass of tower / unique tower type //
//---------------------------------------//

#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include "tower.h"

class StoneBullet {
public:
	Tmpl8::vec2 position;
	Enemy* target;
	float speed = stoneBulletSpeed * cellEdge; // per cell
	float dmg;
	Tmpl8::Sprite* sprite;

	StoneBullet(Tmpl8::vec2 spawnPos, Enemy* target, float dmg);
	void Hit();
	void Render();
};

// all the stone bullets (which are still flying)
extern vector<StoneBullet*> stoneBullets;

class StoneTower : public Tower {

public:
	void Shoot(vector<Enemy*> triggeredEnemies);	// generate (place the tower)
	 
	using Tower::Tower;

	void LvlUp();									// upgrade function
};


#endif // !STONE_TOWER_H