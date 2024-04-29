#include "healthbar.h"

void HealthBar::SetMaxHealth(float maxhp) {
	maxHealth = maxhp;
	percentage = 1.0f;
}

void HealthBar::Update(float presenthp)
{
	percentage = presenthp / maxHealth;
}

void HealthBar::Render(Tmpl8::vec2 enemysPos)
{
	for (int i = 0; i < WIDTH_OF_HEALTH_BAR; i++)
	{
		Tmpl8::vec2 relevantPos = { enemysPos.x - (LENGTH_OF_HEALTH_BAR / 2), enemysPos.y + DOWN_OFFSET };

		screen_->Line(relevantPos.x, relevantPos.y + i, relevantPos.x + LENGTH_OF_HEALTH_BAR, relevantPos.y + i, 0xF35F66); // RED PART (background)
		screen_->Line(relevantPos.x, relevantPos.y + i, relevantPos.x + LENGTH_OF_HEALTH_BAR * percentage, relevantPos.y + i, 0x4FDD79);							// GREEN PART	
	}
}
