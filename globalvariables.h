#pragma once

//---------------------------------------------------//
// That file contains all the varaibles, which can   //
// be used in any script throughout the project      //
//---------------------------------------------------//

#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "template.h"
#include "surface.h"
#include <vector>

using std::vector;

// PI numbers
constexpr float PI = 3.14159265358979323846264338327950288419716939937510582097494459072381640628620899862803482534211706798f;

// screen variable, but global
extern Tmpl8::Surface* screen_;

// mouse position on the screen
extern int xmouse, ymouse;

// all the scenes
enum class Scenes {
	menu,
	playzone,
	pause,
	gameover
};

// game states for gamehandlering
enum class GameState
{
	Loading,
	WaitingForFirstTower,
	WaitingForCooldown,
	SpawningEnemies,
	WaitingForWaveEnd,
	Null
};
// active game state
extern GameState presentGameState;

// tower elements, also available for enemies, to determine the resistance state
enum class Element {
	flame,
	stone,
	snow,
	ice,
	null
};

// structure to draw ambience (randomized background for the game)
struct Ambient
{
	Tmpl8::Sprite* sprite;
	unsigned short x;
	unsigned short y;
	unsigned short frame; // frame of Sprite

	Ambient(Tmpl8::Sprite *sprite, int x, int y, unsigned short frame) :
		sprite(sprite),
		x(x),
		y(y),
		frame(frame)
	{}
};

// active scene
extern Scenes presentScene;

// speed of game
extern float timeKoef;

// amount of time to show change in gold, wave and hp
const float milSecsToShowChangeInVariables = 2000.0f;

// structure for gold, wave and hp
struct MainInfo
{
	unsigned int quan;				// exact quantity
	bool doShowChange;				// detects > if it is changed
	float changeDeltaTime;			// amount of passed time the change was shown
	unsigned int ChangeDigit;		// the change (in quantity)
};

// our main varaibles
extern MainInfo wave;
extern MainInfo castleHP;
extern MainInfo gold;

// function to draw towers' radii
void DrawRadius(float r, float x, float y, Tmpl8::Pixel c);

// function to change gold, wave or hp and start to show that change
void ChangeMainInfo(MainInfo* main, int number);

// function to blend the background (used while game is paused and when panel with tower's info is shown)
void Blend(Tmpl8::Surface* surf, Tmpl8::Pixel cnew, float alpha, int x1, int y1, int x2, int y2);

// statistic-varaibles, they are shown when the game is over
extern unsigned int spendGold;
extern float doneDamage;


#pragma region TOWER_PARAMETERS
//----------------------------//
// START PARAMETERS OF TOWERS //
//----------------------------//
#define NUMBER_OF_TOWER_TYPES 4

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
// STONE TOWER
//
const int stonePrice = 500;
const float stoneDmg = 5.0f;
const float stoneRad = 1.5f;					// in cells
const int stoneLvlUpCost = 750;
const float stoneCoolDown = 0.25f;				// in secs
const int stoneSellCost = 400;
const Tmpl8::Pixel stoneColor = 0x075A44;		// to draw tower's radius

const float stoneBulletSpeed = 5.0f;			// passed cells per sec

// Upgrade parameters (used when the tower is upgraded)
const float additionalStoneDmg = 5.0f;
const float additionalStoneRad = 0.0f;

const float additionalStoneCoolDown = 0.0f;

const int additionalStoneLvlUpCost = 250;


// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
// SNOW TOWER
//
const int snowPrice = 700;
const float snowDmg = 10.0f;
const float snowRad = 2.25f;					// in cells
const int snowLvlUpCost = 1000;
const float snowCoolDown = 1.0f;				// in secs
const int snowSellCost = 525;
const Tmpl8::Pixel snowColor = 0xFFFFFF;		// to draw tower's radius

const float snowBallSpeed = 3.0f;				// passed cells per sec
const float snowBallRad = 0.75f;				// damage radius

// Upgrade parameters (used when the tower is upgraded)
const float additionalSnowDmg = 15.0f;
const float additionalSnowRad = 0.0f;

const float additionalSnowCoolDown = 0.0f;

const float additionalSnowBallSpeed = 0.0f;
const float additionalSnowBallRad = 0.0f;

const int additionalSnowLvlUpCost = 300;


// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
// ICE TOWER
//
const int icePrice = 1500;
const float iceDmg = 0;
const float iceRad = 1.75f;						// in cells
const int iceLvlUpCost = 2000;
const float iceCoolDown = 0.0f;					// in secs
const int iceSellCost = 1200;
const Tmpl8::Pixel iceColor = 0x00D2FF;			// to draw tower's radius

const float iceFutureSpeedKoef = 0.8f;			// speed multiplier of enemies, when they are in a range of tower

// Upgrade parameters (used when the tower is upgraded)
const float additionalIceDmg = 0.0f;
const float additionalIceRad = 0.0f;

const float additionalIceCoolDown = 0.0f;

const float additionalIceFutureSpeedKoef = -0.05f;
const int additionalIceLvlUpCost = 500;



// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
// FLAME TOWER
//
const int flamePrice = 450;
const float flameDmg = 0.15f;					// per 100 ms
const float flameRad = 2.5f;					// in cells
const int flameLvlUpCost = 600;
const float flameCoolDown = 0.1f;				// there are these 100 ms (in secs)
const int flameSellCost = 325;
const Tmpl8::Pixel flameColor = 0xFF8933;		// to draw tower's radius

// Upgrade parameters (used when the tower is upgraded)
const float additionalFlameDmg = 0.075f;
const float additionalFlameRad = 0.0f;

const float additionalFlameCoolDown = 0.0f;

const int additionalFlameLvlUpCost = 150;


// ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
// SPRITES MUST BE DEFINED DIRECTLY IN PLAYZONE.CPP FILE
#pragma endregion



#pragma region PLAYFIELD_PARAMETERS
//----------------------//
// PLAYFIELD PARAMETRES //
//----------------------//

const int PLAYFIELD_L_BORDER = 143;			// LEFT
const int PLAYFIELD_R_BORDER = 657;			// RIGHT
const int PLAYFIELD_T_BORDER = 143;			// TOP
const int PLAYFIELD_B_BORDER = 657;			// BOTTOM
const int NUMBER_OF_ROWS = 8;				// On playfield
const int NUMBER_OF_COLUMNS = 8;			// On playfield
const int INDENT_IN_PX_FROM_EDGES = 1;		// Added simply for math logic ////// edge of whole playfield, not of each cell


const int columnsToFulfilByAmbience = 8;	// used to draw a nice background
const int rowsToFulfilByAmbience = 8;		//			 -- || --


// arrays with background objects' positions
extern vector<Ambient*> ambience;			// used in menu and game-over scenes
extern vector<Ambient*> ambiencePZ;			// used in pause and playzone scenes


// variables for math
const float playfieldWidth = PLAYFIELD_R_BORDER - 2.0f * INDENT_IN_PX_FROM_EDGES - PLAYFIELD_L_BORDER;
const float playfieldHeight = PLAYFIELD_B_BORDER - 2.0f * INDENT_IN_PX_FROM_EDGES - PLAYFIELD_T_BORDER;
const float cellEdge = playfieldWidth / NUMBER_OF_COLUMNS; // !!!!!!!!!!!!!!!!!!!!!! Edges must be same, it is meant that cell must be a square!


const int NUMBER_OF_FIELD_PARTS_HORIZ = 4;	// devides the field horizontally and vertically
const int NUMBER_OF_FIELD_PARTS_VERT = 4;	// to randomize the route (enemy's path)


extern bool pathGridBool[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];	// varaibles for math
extern short pathGridShort[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];	// to randomize the route (enemy's path)

#pragma endregion



#pragma region ENEMIES
//------------------------
// PARAMETERS OF ENEMIES
//------------------------

// ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
// WAVE IS USED AS A KOEFICIENT FOR CALCULATIONS >>> WATCH GAME_HANDLER FOR MATH

extern Tmpl8::vec2 spawnEnemyPos;
const float milSecsToWaitForTheNextEnemy = 500.0f;	// delay between enemys' spawns in milSecs
const float milSecsToWaitBeforeWave = 3000.0f;		// delay between waves in milSecs

#define NUMBER_OF_ENEMYS_TYPE 7

// structure to make a type of enemy
struct EnemysType {
	float hp;
	float hpKoef;			// additional hp, increases when wave is increased
	int rewardPrice;		// reward for killing an enemy
	int rewardForKoef;		// additional reward, increases when wave is increased
	float speed;			// per cell
	Element resistance;		// resistance toward the towers with same Element
	Tmpl8::Sprite* sprite;
	int numberToSpawn;		// per wave
	int castleDMG;			// dmg to igloo, when they reach it

	// Constructor
	EnemysType(float hp, int rewardPrice, float speed, Element resistance, float additionalHP, int numberOfEnemies, Tmpl8::Sprite* sprite, int castleDMG, int rewardForKoef) :
		hp(hp),
		rewardPrice(rewardPrice),
		speed(speed),
		resistance(resistance),

		hpKoef(additionalHP),
		sprite(sprite),
		numberToSpawn(numberOfEnemies),
		castleDMG(castleDMG),

		rewardForKoef(rewardForKoef)
	{}
};

// enemies are declared in globalvaraibles.cpp
extern EnemysType enemysType[NUMBER_OF_ENEMYS_TYPE];
#pragma endregion



//------------------//
// PANEL PARAMETERS	//
//------------------//

const int PANEL_HEIGHT = 210;
const int PANEL_WIDTH = 210;



//------------//
// HEALTH BAR //
//------------//

constexpr int WIDTH_OF_HEALTH_BAR = 2;		// px
constexpr int LENGTH_OF_HEALTH_BAR = 24;	// px
constexpr int DOWN_OFFSET = 10;				// px

#endif // !GLOBALVARIABLES_H