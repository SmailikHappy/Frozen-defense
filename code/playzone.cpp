#include "playzone.h"

// button sprites and buttons

Tmpl8::Sprite pauseSpritePZ(new Tmpl8::Surface("assets/buttons/playzone/pause.png"), 3);
Tmpl8::Sprite speed1SpritePZ(new Tmpl8::Surface("assets/buttons/playzone/speed1.png"), 3);
Tmpl8::Sprite speed2SpritePZ(new Tmpl8::Surface("assets/buttons/playzone/speed2.png"), 3);

Button pauseButtonPZ{ true, 738.0f, 62.0f, &pauseSpritePZ, ButtonType::pause };
Button speed1ButtonPZ{ true, 62.0f, 62.0f, &speed1SpritePZ, ButtonType::speed1 };
Button speed2ButtonPZ{ false, 62.0f, 62.0f, &speed2SpritePZ, ButtonType::speed2 };

Button* playZoneButtons[PLAYZONE_BUTTONS] = { &pauseButtonPZ, tPanel.upgradeTower, tPanel.sellTower, tPanel.back, &speed1ButtonPZ, &speed2ButtonPZ };

Tmpl8::Sprite goldSpr(new Tmpl8::Surface("assets/playzone/gold.png"), 1);
Tmpl8::Sprite waveSpr(new Tmpl8::Surface("assets/playzone/wave.png"), 1);
Tmpl8::Sprite hpSpr(new Tmpl8::Surface("assets/playzone/hp.png"), 1);

Tmpl8::Sprite playField(new Tmpl8::Surface("assets/playzone/playfield.png"), 1);
Tmpl8::Sprite background(new Tmpl8::Surface("assets/background.png"), 1);
Tmpl8::Sprite leftPath(new Tmpl8::Surface("assets/playzone/additionalL.png"), 1);
Tmpl8::Sprite rightPath(new Tmpl8::Surface("assets/playzone/additionalR.png"), 1);
Tmpl8::Sprite pathTilesSpr(new Tmpl8::Surface("assets/playzone/pathgridtiles.png"), 16);	// tile-path

Tmpl8::Sprite stoneSpr(new Tmpl8::Surface("assets/playzone/towers/stone.png"), 2);
Tmpl8::Sprite snowSpr(new Tmpl8::Surface("assets/playzone/towers/snow.png"), 2);
Tmpl8::Sprite iceSpr(new Tmpl8::Surface("assets/playzone/towers/ice.png"), 2);
Tmpl8::Sprite flameSpr(new Tmpl8::Surface("assets/playzone/towers/flame.png"), 2);

// draggers

TowerDragger stoneTowerDragger{ &stoneSpr, 174.0f, 729.0f, Element::stone };
TowerDragger snowTowerDragger{ &snowSpr, 326.0f, 729.0f, Element::snow };
TowerDragger iceTowerDragger{ &iceSpr, 475.0f, 729.0f, Element::ice };
TowerDragger flameTowerDragger{ &flameSpr, 626.0f, 729.0f, Element::flame };

unsigned short leftPathY;
unsigned short rightPathY;

TowerDragger* draggers[NUMBER_OF_TOWER_TYPES] =
{
	&stoneTowerDragger,
	&snowTowerDragger, 
	&iceTowerDragger,
	&flameTowerDragger
};

void UpdatePlayZone(float deltatime)
{
	// draws a background
	background.Draw(screen_, 0, 0);

	// draws ambient objects
	for (Ambient* object : ambiencePZ)
	{
		object->sprite->SetFrame(object->frame);
		object->sprite->Draw(screen_, object->x - object->sprite->GetWidth() / 2, object->y - object->sprite->GetHeight() / 2);
	}

	// other parts of visual
	playField.Draw(screen_, PLAYFIELD_L_BORDER, PLAYFIELD_T_BORDER);
	leftPath.Draw(screen_, 0, leftPathY - leftPath.GetHeight() / 2 + INDENT_IN_PX_FROM_EDGES);
	rightPath.Draw(screen_, PLAYFIELD_R_BORDER - INDENT_IN_PX_FROM_EDGES, rightPathY - rightPath.GetHeight() / 2 - (int) cellEdge / 2 + INDENT_IN_PX_FROM_EDGES);

	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if (pathGridBool[j][i]) {
				pathTilesSpr.SetFrame(pathGridShort[j][i]);
				pathTilesSpr.Draw(screen_, PLAYFIELD_L_BORDER + INDENT_IN_PX_FROM_EDGES + (int) cellEdge * i, PLAYFIELD_T_BORDER + INDENT_IN_PX_FROM_EDGES + (int) cellEdge * j);
			}
		}
	}

	// important info printing
	goldSpr.Draw(screen_, 250 - goldSpr.GetWidth() - 3, 65 - goldSpr.GetHeight() / 2);
	PrintInfo(&gold, 250, deltatime);
	waveSpr.Draw(screen_, 400 - waveSpr.GetWidth() - 3, 65 - waveSpr.GetHeight() / 2);
	PrintInfo(&wave, 400, deltatime);
	hpSpr.Draw(screen_, 550 - hpSpr.GetWidth() - 3, 65 - hpSpr.GetHeight() / 2);
	PrintInfo(&castleHP, 550, deltatime);

	// show towers
	for (Tower *tower : towers){
		if (!tower) continue;
		if (!tower->isActive) continue;
		tower->RenderTower();
	} 

	// show bullets
	for (StoneBullet* bullet : stoneBullets){
		bullet->Render();
	}

	// show snowballs
	for (SnowBall* ball : snowBalls){
		ball->Render();
	}

	// snow 'dragged' towers
	for (TowerDragger* towerDragger : draggers){
		towerDragger->RenderTowerDragger();
	}

	// Render only alived enemies
	for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++){
		if (enemies[i].isAlive) enemies[i].Render();
	}

	// show buttons
	for (Button* button : playZoneButtons) {
		button->Render();
	}

	if (tPanel.isActive) tPanel.Render(); // show the info-panel
}

void PrintInfo(MainInfo* main, int xPos, float deltatime)
{
	char str[32];
	sprintf(str, "%i", main->quan);
	screen_->Print(str, xPos, 65, 0x0AA8F0);

	if (main->doShowChange) ShowChange(deltatime, &main->doShowChange, &main->changeDeltaTime, main->ChangeDigit, xPos);
}

void ShowChange(float deltatime, bool* var1, float* timer, int number, int xPos)
{
	if (*timer > milSecsToShowChangeInVariables) {
		*var1 = false;
		return;
	}

	*timer += deltatime;

	char str[32];
	Tmpl8::Pixel color = 0x000000;
	if (number < 0)
	{
		color = 0xE43A36;
		sprintf(str, "%i", number);
	}
	if (number > 0)
	{
		color = 0x54A858;
		sprintf(str, "%i", number); // PLUS IS NOT WORKING!!!!!
	}

	screen_->Print(str, xPos, 90, color);
}