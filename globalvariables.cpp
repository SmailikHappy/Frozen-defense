#include "globalvariables.h"
// declaration
GameState presentGameState = GameState::Null;


MainInfo wave;
MainInfo castleHP;
MainInfo gold;


bool pathGridBool[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];
short pathGridShort[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];


float timeKoef;


vector<Ambient*> ambience;
vector<Ambient*> ambiencePZ;


// function to draw towers' radii
void DrawRadius(float radius, float x, float y, Tmpl8::Pixel color)
{
	for (int i = 0; i < 128; i++)	// draw 128 lines
	{
		float r1 = (float)i * PI / 64;			// line's start value (radians)
		float r2 = (float)(i + 1) * PI / 64;	// line's end value	(radians)
		screen_->Line(x - radius * sinf(r1), y - radius * cosf(r1),		// start point of line
					  x - radius * sinf(r2), y - radius * cosf(r2), color);	// end point of line and color
	}
}

// function to change gold, wave or hp and start to show that change
void ChangeMainInfo(MainInfo* main, int number)
{
	main->quan += number;					// new quantity
	main->ChangeDigit = number;				// sets the difference
	main->doShowChange = true;				// enables change
	main->changeDeltaTime = 0.0f;			// clears passed time value
}

// function to blend the background (used while game is paused and when panel with tower's info is shown)
void Blend(Tmpl8::Surface* surf, Tmpl8::Pixel cnew, float alpha, int x1, int y1, int x2, int y2)
{
	Tmpl8::Pixel* buffer = surf->GetBuffer();
	int width = surf->GetWidth();

	for (int x = x1; x < x2; x++)					// goes through all x's
	{
		for (int y = y1; y < y2; y++)				// goes through all y's
		{
			// calculation of blend
			Tmpl8::Pixel r = (int) ((1.0 - alpha) * (buffer[x + y * width] & Tmpl8::RedMask) + alpha * (cnew & Tmpl8::RedMask)) & Tmpl8::RedMask;
			Tmpl8::Pixel g = (int) ((1.0 - alpha) * (buffer[x + y * width] & Tmpl8::GreenMask) + alpha * (cnew & Tmpl8::GreenMask)) & Tmpl8::GreenMask;
			Tmpl8::Pixel b = (int) ((1.0 - alpha) * (buffer[x + y * width] & Tmpl8::BlueMask) + alpha * (cnew & Tmpl8::BlueMask)) & Tmpl8::BlueMask;

			buffer[x + y * width] = r + g + b;		// output, set the color
		}
	}
}

// declaration
unsigned int spendGold;
float doneDamage;

// sprites of enemies
Tmpl8::Sprite normalEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/normal.png"), 1);
Tmpl8::Sprite fastEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/fast.png"), 1);
Tmpl8::Sprite bossEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/boss.png"), 1);
Tmpl8::Sprite stonixEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/stonix.png"), 1);
Tmpl8::Sprite snowixEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/snowix.png"), 1);
Tmpl8::Sprite icixEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/icix.png"), 1);
Tmpl8::Sprite flamixEnemySpr(new Tmpl8::Surface("assets/playzone/enemies/flamix.png"), 1);

//different tyoes of enemies
EnemysType normal(10.0f, 30, 1.5f, Element::null, 5.0f, 20, &normalEnemySpr, 1, 4);
EnemysType fast(5.0f, 30, 3.0f, Element::null, 5.0f, 20, &fastEnemySpr, 1, 4);
EnemysType boss(100.0f, 500, 1.5f, Element::null, 75.0f, 1, &bossEnemySpr, 5, 80);
EnemysType stonix(10.0f, 30, 1.2f, Element::stone, 5.0f, 20, &stonixEnemySpr, 1, 4);
EnemysType snowix(20.0f, 60, 0.5f, Element::snow, 10.0f, 10, &snowixEnemySpr, 2, 8);
EnemysType icix(8.5f, 30, 1.5f, Element::ice, 4.5f, 20, &icixEnemySpr, 1, 4);
EnemysType flamix(15.0f, 60, 0.85f, Element::flame, 7.5f, 10, &flamixEnemySpr, 2, 8);

// declaration
EnemysType enemysType[NUMBER_OF_ENEMYS_TYPE] = {
	normal,
	fast,
	boss,
	stonix,
	snowix,
	icix,
	flamix
};