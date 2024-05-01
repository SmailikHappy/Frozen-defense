#pragma once

//---------------------//
// tower-dragger class //
//---------------------//

#ifndef TOWER_DRAGGER_H
#define TOWER_DRAGGER_H

// towers
#include "stonetower.h"
#include "snowtower.h"
#include "icetower.h"
#include "flametower.h"

class TowerDragger {

public:
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2 startPosition;
	bool isHovered = false;
	bool isTaken = false;
	Element element;

	int leftBorder, rightBorder, topBorder, botBorder;

	TowerDragger(Tmpl8::Sprite* sprite, float x, float y, Element element);
	void RenderTowerDragger();	// render it

private:
	void CalculateBorders();	// calc the borders (to make it interactable)
};

#endif