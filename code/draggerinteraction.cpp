#include "draggerinteraction.h"

void CheckDraggerTake()							
{
	for (TowerDragger* towerDragger : draggers)
	{
		// if there were not enough gold
		if (towerDragger->element == Element::stone && gold.quan < stonePrice) continue;
		if (towerDragger->element == Element::snow && gold.quan < snowPrice) continue;
		if (towerDragger->element == Element::ice && gold.quan < icePrice) continue;
		if (towerDragger->element == Element::flame && gold.quan < flamePrice) continue;

		// triggers to take it
		if (towerDragger->leftBorder < xmouse &&
			towerDragger->rightBorder > xmouse &&
			towerDragger->topBorder < ymouse &&
			towerDragger->botBorder > ymouse)
		{
			towerDragger->isTaken = true;
		} 
	}
}

void CheckDraggerRelease()						
{
	for (TowerDragger* towerDragger : draggers)
	{
		if (towerDragger->isTaken) {
			towerDragger->isTaken = false;
			PlaceTower(*towerDragger);
		}
	}
}