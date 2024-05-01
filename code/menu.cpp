#include "menu.h"

Tmpl8::Sprite playSpriteM(new Tmpl8::Surface("assets/buttons/menu/playButton.png"), 3);
Tmpl8::Sprite exitSpriteM(new Tmpl8::Surface("assets/buttons/menu/exitButton.png"), 3);

Tmpl8::Sprite backgroundM(new Tmpl8::Surface("assets/background.png"), 1);
Tmpl8::Sprite logoM(new Tmpl8::Surface("assets/logo.png"), 1);

Button playButtonM(true, 400.0f, 400.0f, &playSpriteM, ButtonType::play);
Button exitButtonM(true, 400.0f, 550.0f, &exitSpriteM, ButtonType::quit);

Button* menuButtons[MENU_BUTTONS] = { &playButtonM, &exitButtonM };
 
void UpdateMenu() {
	// Draw buttons
	backgroundM.Draw(screen_, 0, 0);

	for (Ambient* object : ambience)
	{
		object->sprite->SetFrame(object->frame);
		object->sprite->Draw(screen_, object->x - object->sprite->GetWidth() / 2, object->y - object->sprite->GetHeight() / 2 );
	}

	logoM.Draw(screen_, 400 - logoM.GetWidth() / 2, 200 - logoM.GetHeight() / 2);

	for (Button* button : menuButtons) {
		button->Render();
	}
}