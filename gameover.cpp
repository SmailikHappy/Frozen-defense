#include "gameover.h"

Tmpl8::Sprite returnSpriteSprGO(new Tmpl8::Surface("assets/buttons/pause/exitButton.png"), 3);
Tmpl8::Sprite gameOverSprGO(new Tmpl8::Surface("assets/gameover.png"), 1);
Tmpl8::Sprite backgroundGO(new Tmpl8::Surface("assets/background.png"), 1);

Button returnToMenuGO{ true, 400.0f, 600, &returnSpriteSprGO, ButtonType::backtomenu };

Button* gameOverButtons[GAMEOVER_BUTTONS] = { &returnToMenuGO };

char str_[3][64];

void LoadGameOverInfo()
{
	sprintf(str_[0], "You have reached %i wave", wave.quan);
	sprintf(str_[1], "You have spent %i coins generally", spendGold);
	sprintf(str_[2], "You have done %.2f units of damage", doneDamage);
}

void UpdateGameOver()
{
	backgroundGO.Draw(screen_, 0, 0);

	for (Ambient* object : ambience)
	{
		object->sprite->SetFrame(object->frame);
		object->sprite->Draw(screen_, object->x - object->sprite->GetWidth() / 2, object->y - object->sprite->GetHeight() / 2);
	}

	for (Button* button : gameOverButtons) {
		button->Render();
	}

	screen_->Print(str_[0], 300, 390, 0x7CBDE4);
	screen_->Print(str_[1], 300, 420, 0x7CBDE4);
	screen_->Print(str_[2], 300, 450, 0x7CBDE4);

	gameOverSprGO.Draw(screen_, 400 - gameOverSprGO.GetWidth() / 2, 200 - gameOverSprGO.GetHeight() / 2);
}