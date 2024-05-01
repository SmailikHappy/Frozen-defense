#pragma once

//------------------------------------------------//
// That file is only for grouping scenes.h in one //
// place and update them each frame				  //
//------------------------------------------------//

#ifndef SCENES_H
#define SCENES_H

// #include "scene.h" (scenes)
#include "menu.h"
#include "playzone.h"
#include "pause.h"
#include "gameover.h"

// each frame updates screen
void UpdateScreen(float deltatime);

#endif // !MENU_H