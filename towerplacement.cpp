#include "towerplacement.h"
#include "FreeImage.h"

// tower sprites
Tmpl8::Sprite stoneSpr_(new Tmpl8::Surface("assets/playzone/towers/stone.png"), 2);
Tmpl8::Sprite snowSpr_(new Tmpl8::Surface("assets/playzone/towers/snow.png"), 2);
Tmpl8::Sprite iceSpr_(new Tmpl8::Surface("assets/playzone/towers/ice.png"), 2);
Tmpl8::Sprite flameSpr_(new Tmpl8::Surface("assets/playzone/towers/flame.png"), 2);

#pragma region TOWER_PLACEMENT
void PlaceTower(TowerDragger towerDragger)
{
	// checks if mouse is not above the playfield
	if (xmouse <= PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES) return;
	if (xmouse >= PLAYFIELD_R_BORDER - INDENT_IN_PX_FROM_EDGES) return;
	if (ymouse <= PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES) return;
	if (ymouse >= PLAYFIELD_B_BORDER - INDENT_IN_PX_FROM_EDGES) return;

	int row = GetRow();
	int column = GetColumn();

	// checks if cell is busy (there is)
	if (pathGridBool[row][column]) return;

	// calculates the coordinates on the screen
	int y = row * (int) cellEdge + PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES + 1;
	int x = column * (int) cellEdge + PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES + 1;

	// starts the game
	isFirstTowerPlaced = true;

	// spawns the tower
	if (towerDragger.element == Element::stone)
	{
		spendGold += stonePrice;							// statistics
		ChangeMainInfo(&gold, -stonePrice);					// changes and show them
		// makes a tower
		StoneTower* tower = new StoneTower(x, y, &stoneSpr_, Element::stone, stoneRad, stoneDmg, stoneLvlUpCost, stoneCoolDown, stoneSellCost);
		towers[row * NUMBER_OF_COLUMNS + column] = tower;	// adds to array
	}
	else if (towerDragger.element == Element::snow)
	{
		spendGold += snowPrice;								// statistics
		ChangeMainInfo(&gold, -snowPrice);					// changes and show them
		SnowTower* tower = new SnowTower(x, y, &snowSpr_, Element::snow, snowRad, snowDmg, snowLvlUpCost, snowCoolDown, snowSellCost);
		towers[row * NUMBER_OF_COLUMNS + column] = tower;	// adds to array
	}
	else if (towerDragger.element == Element::ice)
	{
		spendGold += icePrice;								// statistics
		ChangeMainInfo(&gold, -icePrice);					// changes and show them
		// makes a tower
		IceTower* tower = new IceTower(x, y, &iceSpr_, iceRad, iceDmg, iceLvlUpCost, iceCoolDown, iceSellCost);
		towers[row * NUMBER_OF_COLUMNS + column] = tower;	// adds to array
	}
	else if (towerDragger.element == Element::flame)
	{
		spendGold += flamePrice;							// statistics
		ChangeMainInfo(&gold, -flamePrice);					// changes and show them
		// makes a tower
		FlameTower* tower = new FlameTower(x, y, &flameSpr_, Element::flame, flameRad, flameDmg, flameLvlUpCost, flameCoolDown, flameSellCost);
		towers[row * NUMBER_OF_COLUMNS + column] = tower;	// adds to array
	}
}

int GetRow()
{
	// checks each row and tries to find mouse in it
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		if (i * cellEdge + PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES <= ymouse &&
			ymouse < (i+1) * cellEdge + PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES)
		{
			return i;
		}
	}
	return 0;
}

int GetColumn()
{
	// checks each column and tries to find mouse in it
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		if (i * cellEdge + PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES <= xmouse &&
			xmouse < (i + 1) * cellEdge + PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES)
		{
			return i;
		}
	}
	return 0;
}
#pragma endregion