#pragma once

#include "mouseinteraction.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) {
		if (button == 1) CheckMouseUp();
	}
	void MouseDown(int button) {
		if (button == 1) CheckMouseDown();
	}
	void MouseMove(int x, int y) { xmouse = x, ymouse = y; } // GLOBAL VARIABLES
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
};

}; // namespace Tmpl8