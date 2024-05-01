#include "scenemanager.h"

void UpdateScreen(float deltatime) {
	// checks the scene, then calls the function (of scene) to update it
	switch (presentScene)
	{
	case Scenes::menu:
		UpdateMenu();
		break;
	case Scenes::playzone:
		UpdatePlayZone(deltatime);
		break;
	case Scenes::pause:
		UpdatePause();
		break;
	case Scenes::gameover:
		UpdateGameOver();
		break;
	}
}