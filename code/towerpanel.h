#pragma once

//------------------//
// info panel class //
//------------------//

#ifndef TOWER_PANEL_H
#define TOWER_PANEL_H

#include "stonetower.h"
#include "snowtower.h"
#include "icetower.h"
#include "flametower.h"
#include "button.h"


enum class ButtonFunc	// type of buttons
{
	upgrade,
	sell,
	back
};


class PanelButton : public Button
{
public:
	using Button::Button;

	void SetPos(float x, float y);		// to draw it on that position
};



class TPanel
{
public:
	int leftBorder, topBorder, rightBorder, bottomBorder;
	bool isActive = false;
	int upgradePrice;
	int sellPrice;
	Tower* selectedTower;
	unsigned short towersIDInArray;

	PanelButton* upgradeTower;		// buttons to interact
	PanelButton* sellTower;
	PanelButton* back;



	TPanel();

	void ShowInfo(Tower* tower, unsigned short id);		// make panel active
	void HideInfo();									// hide it
	void Render();										// show it

private:
	void SetTextOnPanel();								// calc the text
	void RenderText();									// show the text
	void SetBorders(Tower* tower);						// borders for interaction
};

#endif // !TOWER_BUTTON_H