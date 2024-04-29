#pragma once

//--------------------------------------------//
// Here the ambient objects are generated and //
// randomized and inserted into arrays		  //
//--------------------------------------------//

#ifndef VISUAL_HANDLER_H
#define VISUAL_HANDLER_H

#include "globalvariables.h"

void GenerateAmbience();
void GenerateAmbienceInPlayZone(unsigned short starty, unsigned short finishy); // Y level of start path (outside of playfield)
																				// Y level of finish path (outside of playfield)
#endif // !VISUAL_HANDLER_H