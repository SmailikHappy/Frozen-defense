#pragma once

//----------------------------------------------------------//
// There is a code to place the towers in a plafield's cell //
//----------------------------------------------------------//

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "gamehandler.h"

void PlaceTower(TowerDragger towerDragger);

// Gets row of playfield (from screnn coords)
int GetRow();

// Gets column of playfield (from screnn coords)
int GetColumn();
#endif