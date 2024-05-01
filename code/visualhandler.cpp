#include "visualhandler.h"
#include <algorithm>
#include <time.h>

Tmpl8::Sprite spritesOfAmbience(new Tmpl8::Surface("assets/ambience.png"), 32);

void GenerateAmbience()
{
	srand((unsigned int)time(NULL));								// sets a time-based seed

	for (int i = 0; i < columnsToFulfilByAmbience; i++)				// the object is generated in each 'fantom' column
	{
		for (int j = 0; j < rowsToFulfilByAmbience; j++)			// the object is generated in each 'fantom' row
		{
			int x = rand() % (800 / columnsToFulfilByAmbience);		// randomize X
			int y = rand() % (800 / rowsToFulfilByAmbience);		// randomize Y
			unsigned short frame = rand() % 32;						// randomize frame

			// add to array
			ambience.push_back(new Ambient{ &spritesOfAmbience, x + i * (800 / columnsToFulfilByAmbience), y + j * (800 / rowsToFulfilByAmbience), frame});
		}
	}
}

void GenerateAmbienceInPlayZone(unsigned short starty, unsigned short finishy)
{
	for (Ambient* object : ambience)		// gets already made array
	{
		// checks if object is on the left side from playfield
		if (object->x + object->sprite->GetWidth() / 2 < PLAYFIELD_L_BORDER - 5)
			// checks if object do not collide with start path
			if (object->y + object->sprite->GetHeight() / 2 < starty - cellEdge / 2 ||
				object->y - object->sprite->GetHeight() / 2 > starty + cellEdge / 2)

				// add to array
				ambiencePZ.push_back(object);


		// checks if object is on the left side from playfield
		if (object->x - object->sprite->GetWidth() / 2 > PLAYFIELD_R_BORDER + 5)
			// checks if object do not collide with finish path
			if (object->y + object->sprite->GetHeight() / 2 < finishy - cellEdge ||
				object->y - object->sprite->GetHeight() / 2 > finishy + cellEdge)

				// add to array
				ambiencePZ.push_back(object);

		// these two ifs checks if object is above the playfield
		if (object->x + object->sprite->GetWidth() / 2 >= PLAYFIELD_L_BORDER - 5 && object->x - object->sprite->GetWidth() / 2 <= PLAYFIELD_R_BORDER + 5)
			if (object->y + object->sprite->GetHeight() / 2 < PLAYFIELD_T_BORDER - 5)

				// add to array
				ambiencePZ.push_back(object);
	}
}