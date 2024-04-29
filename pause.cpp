#include "pause.h"

// buttons and sprites

Tmpl8::Sprite returnSpriteSpr(new Tmpl8::Surface("assets/buttons/pause/exitButton.png"), 3);
Tmpl8::Sprite unpauseGameSpr(new Tmpl8::Surface("assets/buttons/pause/playbutton.png"), 3);

Button returnToMenu{ true, 400.0f, 400.0f, &returnSpriteSpr, ButtonType::backtomenu };
Button unpauseGame{ true, 400.0f, 550.0f, &unpauseGameSpr, ButtonType::unpause };

Button* pauseButtons[PAUSE_BUTTONS] = {&returnToMenu, &unpauseGame};

void UpdatePause()
{
	for (Button* button : pauseButtons) {
		button->Render();
	}
}