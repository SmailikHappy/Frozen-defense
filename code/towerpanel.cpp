#include "towerpanel.h"
#include <string>


Tmpl8::Sprite upgradeButtonBackground(new Tmpl8::Surface("assets/playzone/panel/upgradepanel.png"), 3);
Tmpl8::Sprite sellButtonBackground(new Tmpl8::Surface("assets/playzone/panel/sellpanel.png"), 3);
Tmpl8::Sprite backButtonBackground(new Tmpl8::Surface("assets/playzone/panel/backpanel.png"), 3);

const unsigned short numberOfLines = 5;
char str[numberOfLines][64];

void PanelButton::SetPos(float x, float y) {
	position = { x, y };
	CalculateBorders();
}

TPanel::TPanel()
{
	upgradeTower = new PanelButton(false, 0, 0, &upgradeButtonBackground, ButtonType::upgrade);
	sellTower = new PanelButton(false, 0, 0, &sellButtonBackground, ButtonType::sell);
	back = new PanelButton(false, 0, 0, &backButtonBackground, ButtonType::back);
}

void TPanel::ShowInfo(Tower* tower, unsigned short id)
{
	// all the important info of the tower is defined
	selectedTower = tower;
	towersIDInArray = id;
	isActive = true;

	upgradeTower->isActive = true;
	sellTower->isActive = true;
	back->isActive = true;
	
	SetBorders(tower);

	upgradePrice = tower->lvlUpCost;
	sellPrice = tower->sellCost;

	SetTextOnPanel();

	upgradeTower->SetPos((float) leftBorder + 40, (float) topBorder + 40);
	sellTower->SetPos((float) leftBorder + 105, (float) topBorder + 40);
	back->SetPos((float) leftBorder + 170, (float) topBorder + 40);


}

void TPanel::HideInfo()
{
	isActive = false;

	upgradeTower->isActive = false;
	sellTower->isActive = false;
	back->isActive = false;
}

void TPanel::SetBorders(Tower* tower)
{
	if (tower->position.x < screen_->GetWidth() / 2) {
		leftBorder = (int) tower->position.x + (int) cellEdge / 2 + 15;
		topBorder = (int) tower->position.y - PANEL_HEIGHT / 2;
		rightBorder = leftBorder + PANEL_WIDTH;
		bottomBorder = topBorder + PANEL_HEIGHT;
	}
	else
	{
		rightBorder = (int) tower->position.x - (int)cellEdge / 2 - 15;
		topBorder = (int) tower->position.y - PANEL_HEIGHT / 2;
		leftBorder = rightBorder - PANEL_WIDTH;
		bottomBorder = topBorder + PANEL_HEIGHT;
	}
}

void TPanel::SetTextOnPanel()
{
	

	switch (this->selectedTower->towerelement)
	{
		case Element::stone:
			sprintf(str[0], "TOWER ELEMENT: STONE");
			sprintf(str[4], "DAMAGE: %.2f", this->selectedTower->damage);
			break;
		case Element::snow:
			sprintf(str[0], "TOWER ELEMENT: SNOW");
			sprintf(str[4], "DAMAGE: %.2f", this->selectedTower->damage);
			break;
		case Element::ice:
			sprintf(str[0], "TOWER ELEMENT: ICE");

			sprintf(str[4], "SLOWNESS MULTIPLIER: %.2f", static_cast<IceTower*>(this->selectedTower)->futureSpeedKoef);
			break;
		case Element::flame:
			sprintf(str[0], "TOWER ELEMENT: FLAME");
			sprintf(str[4], "DAMAGE PER SECOND: %.2f", this->selectedTower->damage / this->selectedTower->cooldown * 1000.0f);
			break;
	}

	sprintf(str[1], "LVL: % i", this->selectedTower->lvl);
	if (this->selectedTower->lvl == 7) sprintf(str[2], "UPGRADE: -");
	else sprintf(str[2], "UPGRADE: % i", this->selectedTower->lvlUpCost);
	sprintf(str[3], "SELL: % i", this->selectedTower->sellCost);
}

void TPanel::Render()
{
	DrawRadius(selectedTower->radius, selectedTower->position.x, selectedTower->position.y, selectedTower->color);

	Blend(screen_, 0x7F7F7F, 0.6f, leftBorder, topBorder, rightBorder, bottomBorder);

	this->RenderText();

	if (this->selectedTower->lvl == 7 || gold.quan < (unsigned int) this->selectedTower->lvlUpCost) upgradeTower->isInteractive = false;
	else upgradeTower->isInteractive = true;

	upgradeTower->Render();
	sellTower->Render();
	back->Render();
}

void TPanel::RenderText()
{
	for (int i = 0; i < numberOfLines; i++)
	{
		screen_->Print(str[i], leftBorder + 15, topBorder + 80 + i * 10, 0xffffff);
	}
}