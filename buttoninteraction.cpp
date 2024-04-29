#include "buttoninteraction.h"

extern int exitapp;

#pragma region BUTTONS
void OnMouseUp(Button* button) {

	// defines the triggere button and executes correct function
	switch (button->buttonType) {
	case ButtonType::play:
		presentScene = Scenes::playzone;
		SetGameState(GameState::Loading);
		break;

	case ButtonType::openlevelmenu:
		break;

	case ButtonType::options:
		break;
		
	case ButtonType::quit:
		exitapp = 1;
		break;

	case ButtonType::pause:
		Blend(screen_, 0xffffff, 0.5f, 0, 0, 800, 800);
		presentScene = Scenes::pause;
		break;

	case ButtonType::speed1:
		playZoneButtons[PLAYZONE_BUTTONS - 2]->isActive = false;
		playZoneButtons[PLAYZONE_BUTTONS - 1]->isActive = true;
		timeKoef = 2.0f;
		break;
	
	case ButtonType::speed2:
		playZoneButtons[PLAYZONE_BUTTONS - 2]->isActive = true;
		playZoneButtons[PLAYZONE_BUTTONS - 1]->isActive = false;
		timeKoef = 1.0f;
		break;

	case ButtonType::unpause:
		presentScene = Scenes::playzone;
		break;

	case ButtonType::backtomenu:
		SetGameState(GameState::Null);
		presentScene = Scenes::menu;
		break;

	case ButtonType::upgrade:
		ChangeMainInfo(&gold, -tPanel.selectedTower->lvlUpCost);
		spendGold += tPanel.selectedTower->lvlUpCost;
		tPanel.selectedTower->LvlUp();
		tPanel.ShowInfo(tPanel.selectedTower, tPanel.towersIDInArray);
		break;

	case ButtonType::sell:
		ChangeMainInfo(&gold, tPanel.selectedTower->sellCost);
		delete towers[tPanel.towersIDInArray];
		towers[tPanel.towersIDInArray] = nullptr;
		tPanel.HideInfo();
		break;

	case ButtonType::back:
		tPanel.HideInfo();
		break;
	}
}

// sprite update of the button
void UpdateSprite(Button* button)
{
	if (!button->isInteractive) return;
	
	if (button->isDown && button->isHovered)
	{
		button->sprite->SetFrame(2);
	}
	else if (!button->isDown && button->isHovered)
	{
		button->sprite->SetFrame(1);
	}
	else if (!button->isDown && !button->isHovered)
	{
		button->sprite->SetFrame(0);
	}
}

#pragma endregion