#include "towerinteraction.h"

TPanel tPanel;

void CheckTowerPanel()
{
	if (tPanel.isActive)
	{
		if (xmouse > tPanel.leftBorder &&
			xmouse < tPanel.rightBorder &&
			ymouse > tPanel.topBorder &&
			ymouse < tPanel.bottomBorder)

			return;
	}

	if (xmouse <= PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES ||
		xmouse >= PLAYFIELD_R_BORDER + INDENT_IN_PX_FROM_EDGES ||
		ymouse <= PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES ||
		ymouse >= PLAYFIELD_B_BORDER + INDENT_IN_PX_FROM_EDGES)
	{	// hide it if no tower was triggered
		tPanel.HideInfo();
		return;
	}
	// find a clicked tower
	unsigned short id = GetRow() * NUMBER_OF_COLUMNS + GetColumn();
	Tower* clickedTower = towers[id];

	// show the info and a panel
	if (clickedTower)
		tPanel.ShowInfo(clickedTower, id);
	else
		tPanel.HideInfo();
}