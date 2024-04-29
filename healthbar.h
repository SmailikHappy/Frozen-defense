#pragma once

//-----------------------//
// health bar of enemies //
//-----------------------//

#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "globalvariables.h"

class HealthBar
{
private:
	float maxHealth;
	float percentage = 1.0f;

public:
	void SetMaxHealth(float maxhp);			// max hp of exact enemy
	void Update(float presenthp);			// present hp of exact enemy
	void Render(Tmpl8::vec2 enemysPos);		// render it
};

#endif