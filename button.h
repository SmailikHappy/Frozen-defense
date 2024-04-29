#pragma once

//--------------//
// button class //
//--------------//

#ifndef BUTTON_H
#define BUTTON_H

#include "globalvariables.h"

enum class ButtonType{	// all types of buttons, it is simplier to list them here
	play,
	openlevelmenu,
	options,
	quit,
	pause,
	speed1,
	speed2,
	unpause,
	backtomenu,
	upgrade,
	sell,
	back
};

class Button {

public:
	Tmpl8::vec2 position;			// Position of button (it's centre)
	Tmpl8::Sprite* sprite;			// Sprite of the button
	ButtonType buttonType;			// Type of button, is used to execute correct functions
	float leftBorder, rightBorder, topBorder, botBorder;  // Variables for correct field indication on the screen
	bool isHovered;
	bool isDown;
	bool isActive;
	bool isInteractive = true;


	// Constructor for Button
	explicit Button(bool isActive, float x, float y, Tmpl8::Sprite* sprite, ButtonType buttontype);

	// render it
	void Render() const;

	// Calculates borders of button to make mouse interact it;
	void CalculateBorders();

#pragma endregion
};
#endif // !BUTTON_H