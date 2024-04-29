#include "mouseinteraction.h"

Scenes presentScene;

int xmouse, ymouse;

#pragma region MOUSE_DOWN

void CheckMouseDown() {

	// defines an activee scene and active buttons
	switch (presentScene)
	{
	case Scenes::menu:
		CheckButtonDown(menuButtons, MENU_BUTTONS);
		break;
	case Scenes::playzone:
		CheckButtonDown(playZoneButtons, PLAYZONE_BUTTONS);
		CheckDraggerTake();
		CheckTowerPanel();
		break;
	case Scenes::pause:
		CheckButtonDown(pauseButtons, PAUSE_BUTTONS);
		break;
	case Scenes::gameover:
		CheckButtonDown(gameOverButtons, GAMEOVER_BUTTONS);
		break;
	}
}

// interacts with a button
void CheckButtonDown(Button* buttons[], int k)
{
	for (int i = 0; i < k; i++)
	{
		if (!buttons[i]->isActive) continue;

		if (!buttons[i]->isInteractive) {
			UpdateSprite(buttons[i]);
			continue;
		}

		if (CheckButton(buttons[i]))
		{
			buttons[i]->isDown = true;
			UpdateSprite(buttons[i]);
		}
	}
}

#pragma endregion



#pragma region MOUSE_UP
// defines an activee scene and active buttons
void CheckMouseUp() {

	switch (presentScene)
	{
	case Scenes::menu:
		CheckButtonUp(menuButtons, MENU_BUTTONS);
		break;
	case Scenes::playzone:
		CheckButtonUp(playZoneButtons, PLAYZONE_BUTTONS);
		CheckDraggerRelease();
		break;
	case Scenes::pause:
		CheckButtonUp(pauseButtons, PAUSE_BUTTONS);
		break;
	case Scenes::gameover:
		CheckButtonUp(gameOverButtons, GAMEOVER_BUTTONS);
		break;
	}
}

// interacts with a button
void CheckButtonUp(Button* buttons[], int k)
{
	for (int i = 0; i < k; i++)
	{
		if (!buttons[i]->isActive) continue;

		if (!buttons[i]->isInteractive) {
			UpdateSprite(buttons[i]);
			continue;
		}

		if (CheckButton(buttons[i]) && buttons[i]->isDown)
		{
			buttons[i]->isDown = false;
			OnMouseUp(buttons[i]);
			UpdateSprite(buttons[i]);
		}
	}
}

#pragma endregion



#pragma region MOUSE_HOVER
// defines an activee scene and active buttons
void CheckMouseHover() {

	switch (presentScene)
	{
	case Scenes::menu:
		CheckButtonHovering(menuButtons, MENU_BUTTONS);
		break;
	case Scenes::playzone:
		CheckButtonHovering(playZoneButtons, PLAYZONE_BUTTONS);
		break;
	case Scenes::pause:
		CheckButtonHovering(pauseButtons, PAUSE_BUTTONS);
		break;
	case Scenes::gameover:
		CheckButtonHovering(gameOverButtons, GAMEOVER_BUTTONS);
		break;
	}
}
// interacts with a button
void CheckButtonHovering(Button* buttons[], int k)
{
	for (int i = 0; i < k; i++)
	{
		if (!buttons[i]->isInteractive) {
			UpdateSprite(buttons[i]);
			continue;
		}

		if (CheckButton(buttons[i]))
		{
			buttons[i]->isHovered = true;
		}
		else
		{
			buttons[i]->isHovered = false;
			buttons[i]->isDown = false;
		}
		UpdateSprite(buttons[i]);
	}
}

#pragma endregion


inline bool CheckButton(Button* button)
{
	if (button->leftBorder < xmouse &&
		button->rightBorder > xmouse &&
		button->topBorder < ymouse &&
		button->botBorder > ymouse)
	{
		return true;
	}

	else return false;
}