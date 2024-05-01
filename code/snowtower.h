#pragma once

//---------------------------------------//
// Subclass of tower / unique tower type //
//---------------------------------------//

#ifndef SNOW_TOWER_H
#define SNOW_TOWER_H

#include "tower.h"

class SnowBall {
public:
	Tmpl8::vec2 position;
	Tmpl8::vec2 targetPos;
	float speed; // per cell
	float dmg;
	Tmpl8::Sprite* sprite;
	float radius;

	SnowBall(Tmpl8::vec2 spawnPos, Tmpl8::vec2 targetPos, float dmg, float snowBallSpeed, float snowBallRad);
	void Explode(vector<Enemy*> triggeredEnemies);
	void Render();
};

extern vector<SnowBall*> snowBalls;

class SnowTower : public Tower {

public:
	float projectileSpeed = snowBallSpeed * cellEdge;
	float projectileRad = snowBallRad * cellEdge;

	void Shoot(vector<Enemy*> triggeredEnemies) override;

	using Tower::Tower;

	void LvlUp();											// upgrade function
};

#endif // !SNOW_TOWER_H