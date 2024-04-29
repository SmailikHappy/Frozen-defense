#include "button.h"

Button::Button(bool isActive, float x, float y, Tmpl8::Sprite* sprite, ButtonType buttontype):
	sprite(sprite),
	buttonType(buttontype),
	isActive(isActive),
	position{x, y}
{
	CalculateBorders();
}

void Button::CalculateBorders() {
	this->leftBorder = position.x - sprite->GetWidth() / 2;
	this->rightBorder = position.x + sprite->GetWidth() / 2;
	this->topBorder = position.y - sprite->GetHeight() / 2;
	this->botBorder = position.y + sprite->GetHeight() / 2;
}

void Button::Render() const{
	if (!isInteractive) sprite->SetFrame(1);

	if (isActive)
		sprite->Draw(screen_, (int) leftBorder, (int) topBorder);
}