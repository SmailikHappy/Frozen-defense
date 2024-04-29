#include "towerdragger.h"


TowerDragger::TowerDragger(Tmpl8::Sprite* sprite, float x, float y, Element element) :
	sprite(sprite),
	startPosition({ x - (this->sprite->GetWidth() / 2), y - (this->sprite->GetHeight() / 2) }),
	element(element)
{ 
	CalculateBorders();
}

void TowerDragger::CalculateBorders()
{
	this->leftBorder = (int) startPosition.x;
	this->rightBorder = (int) startPosition.x + this->sprite->GetWidth();
	this->topBorder = (int) startPosition.y;
	this->botBorder = (int) startPosition.y + this->sprite->GetHeight();
}

void TowerDragger::RenderTowerDragger()
{
	// show the price
	char price[8];

	// find which element of the tower-dragger it is
	// and show appropriate information
	switch (this->element)
	{
	case Element::stone:
		sprintf(price, "% i", stonePrice);
		if (gold.quan < stonePrice)
		{
			this->sprite->SetFrame(1);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7F7F7F);
		}
		else
		{
			this->sprite->SetFrame(0);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7CBDE4);
		}
		break;

	case Element::snow:
		sprintf(price, "% i", snowPrice);
		if (gold.quan < snowPrice)
		{
			this->sprite->SetFrame(1);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7F7F7F);
		}
		else
		{
			this->sprite->SetFrame(0);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7CBDE4);
		}
		break;

	case Element::ice:
		sprintf(price, "% i", icePrice);
		if (gold.quan < icePrice)
		{
			this->sprite->SetFrame(1);
			screen_->Print(price, (int) this->startPosition.x + 13, (int) this->startPosition.y + 75, 0x7F7F7F);
		}
		else
		{
			this->sprite->SetFrame(0);
			screen_->Print(price, (int) this->startPosition.x + 13, (int) this->startPosition.y + 75, 0x7CBDE4);
		}
		break;

	case Element::flame:
		sprintf(price, "% i", flamePrice);
		if (gold.quan < flamePrice)
		{
			this->sprite->SetFrame(1);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7F7F7F);
		}
		else
		{
			this->sprite->SetFrame(0);
			screen_->Print(price, (int) this->startPosition.x + 16, (int) this->startPosition.y + 75, 0x7CBDE4);
		}
		break;
	}

	// if the tower dragger is taken (dragged)
	if (this->isTaken)
	{
		this->sprite->Draw(screen_, xmouse - (this->sprite->GetWidth() / 2), ymouse - (this->sprite->GetHeight() / 2));

		switch (this->element) {
		case Element::stone:
			DrawRadius(stoneRad * cellEdge, (float) xmouse, (float) ymouse, stoneColor);
			break;

		case Element::snow:
			DrawRadius(snowRad * cellEdge, (float) xmouse, (float) ymouse, snowColor);
			break;

		case Element::ice:
			DrawRadius(iceRad * cellEdge, (float) xmouse, (float) ymouse, iceColor);
			break;

		case Element::flame:
			DrawRadius(flameRad * cellEdge, (float) xmouse, (float) ymouse, flameColor);
			break;
		}
	}
	else
	{
		this->sprite->Draw(screen_, (int) this->startPosition.x, (int) this->startPosition.y);
	}
}