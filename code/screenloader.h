#pragma once

#ifndef SCREENLOADER_H
#define SCREENLOADER_H

#include "globalvariables.h"

void Updatecreen() {
	if (presentScene == Scenes::menu) {
		UpdateMenu();
	}
	else if (presentScene == Scenes::playzone) {
		UpdatePlayZone();
	}
}

void UpdateMenu() {

}

void UpdatePlayZone() {

}

#endif // !SCREENLOADER_H
