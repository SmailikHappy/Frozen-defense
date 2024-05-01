#include "snowtower.h"

Tmpl8::Sprite snowBallSpr(new Tmpl8::Surface("assets/playzone/bullets/snowball.png"), 1);
vector<SnowBall*> snowBalls;

void SnowTower::Shoot(vector<Enemy*> triggeredEnemies) {

	SnowBall* snowBall = new SnowBall(position, triggeredEnemies[0]->position, damage, projectileSpeed, projectileRad);
	snowBalls.push_back(snowBall);
}

void SnowTower::LvlUp()
{
	damage += additionalSnowDmg;
	lvl++;
	radius += additionalSnowRad * cellEdge;
	sellCost += lvlUpCost - additionalSnowLvlUpCost;
	lvlUpCost += additionalSnowLvlUpCost;
	cooldown += additionalSnowCoolDown;
	projectileSpeed += additionalSnowBallSpeed;
	projectileRad += additionalSnowBallRad * cellEdge;
}

SnowBall::SnowBall(Tmpl8::vec2 spawnPos, Tmpl8::vec2 targetPos, float dmg, float speed, float radius) :
	position(spawnPos),
	targetPos(targetPos),
	dmg(dmg),
	sprite(&snowBallSpr),
	speed(speed),
	radius(radius)
	{}

void SnowBall::Explode(vector<Enemy*> triggeredEnemies)
{
	for (Enemy* enemy : triggeredEnemies)
	{
		enemy->Damage(dmg);
	}
}

void SnowBall::Render()
{
	sprite->Draw(screen_, (int) position.x - sprite->GetWidth() / 2, (int) position.y - sprite->GetHeight() / 2);
}