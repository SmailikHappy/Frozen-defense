#pragma once

//---------------------------------------------------------------//
// This code is responsible for player's interaction using mouse //
//---------------------------------------------------------------//

#ifndef MOUSEINTERACTION_H
#define MOUSEINTERACTION_H

#include "buttoninteraction.h"
#include "draggerinteraction.h"
#include "towerinteraction.h"



#pragma region MOUSE_DOWN
void CheckMouseDown();							// if mouse down
void CheckButtonDown(Button* buttons[], int k);
#pragma endregion


#pragma region MOUSE_UP
void CheckMouseUp();							// if mouse up
void CheckButtonUp(Button* buttons[], int k);
#pragma endregion


#pragma region MOUSE_HOVER
void CheckMouseHover();							// if mouse hover
void CheckButtonHovering(Button* buttons[], int k);
#pragma endregion


inline bool CheckButton(Button* button);		// check the interacted buttons

#endif // !MOUSEINTERACTION_H