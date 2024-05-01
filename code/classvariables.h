#pragma once

//---------------------------------------------//
// That file contains all classes and has some //
// arrays with their objects				   //
//---------------------------------------------//

#ifndef CLASSVARIABLES_H
#define CLASSVARIABLES_H

//#include "tower.h"	INSTEAD OF TOWER_H, THERE ARE TOWER_CHILDS INTEGRATED INTO TOWERDRAGGER_H
#include "towerdragger.h"
#include "button.h"
#include "enemy.h"
#include "towerpanel.h"
#include <vector>
#include <array>
using std::vector;
using std::array;


// array with buttons, which needs to be rendered in menu scene
#define MENU_BUTTONS 2
extern Button* menuButtons[MENU_BUTTONS];


// array with buttons, which needs to be rendered in playzone scene
const int PLAYZONE_BUTTONS = 6;
extern Button* playZoneButtons[PLAYZONE_BUTTONS];


// array with buttons, which needs to be rendered in pause scene
#define PAUSE_BUTTONS 2
extern Button* pauseButtons[PAUSE_BUTTONS];


// array with buttons, which needs to be rendered in gameover scene
#define GAMEOVER_BUTTONS 1
extern Button* gameOverButtons[GAMEOVER_BUTTONS];


// array with tower-draggers 
extern TowerDragger* draggers[NUMBER_OF_TOWER_TYPES];


// array with enemies that will be spawned in a wave time;
#define MAX_NUMBER_OF_ENEMIES 20
extern Enemy enemies[MAX_NUMBER_OF_ENEMIES];


// array with placed towers in playzone
extern array<Tower*, NUMBER_OF_COLUMNS * NUMBER_OF_ROWS> towers;


// tower panel to interact with it
extern TPanel tPanel;


#endif // !CLASSVARIABLES_H

