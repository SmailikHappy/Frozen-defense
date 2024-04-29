#pragma once

//----------------//
// PLAYZONE scene //
//----------------//

#ifndef PLAYZONE_SCENE
#define PLAYZONE_SCENE

#include "classvariables.h"

// start and finish parts of the path
extern unsigned short leftPathY;
extern unsigned short rightPathY;

void UpdatePlayZone(float deltatime);												// updates the scene each frame (if it is enabled)

void ShowChange(float deltatime, bool* var1, float* timer, int number, int xPos);	// shows change in gold, wave and hp

void PrintInfo(MainInfo* main, int xPos, float deltatime);							// prints the color of change (red or green)

Tmpl8::Pixel GetColor(int digit);													// defines the color

#endif // !PLAYZONE_SCENE