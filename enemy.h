#pragma once

//---------------//
// enemy's class //
//---------------//

#ifndef ENEMY_H
#define ENEMY_H

#include "globalvariables.h"
#include "healthbar.h"

class Enemy {
public:
	// all important variables
	bool isAlive = false;
	Tmpl8::Sprite* sprite;
	float speed = 1.5f;		// per cell
	float hp;
	int rewardprice;
	Tmpl8::vec2 position;
	char directionY;						// direction
	char directionX;
	Element resistance;						// resistance toward exact type of towers
	unsigned short castledamage;			// how many hp it will take from the player
	unsigned short routePointToReach = 0;
	HealthBar healthBar;
	float speedKoef = 1.0f;					// is affected by 'froze-tower'



	Enemy(EnemysType* type, int k);			// uses the type of enemy to soawn it
	Enemy();

	void Render();
	void Damage(float dmg);					// damage an enemy (or kill it)
};

#endif // !ENEMY_H