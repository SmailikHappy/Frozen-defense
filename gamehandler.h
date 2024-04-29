#pragma once

//--------------------------------------//
// Main script to handle the whole game //
// and manage all these processes		//
//--------------------------------------//

#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "scenemanager.h"
#include "visualhandler.h"

// variable to start the game
extern bool isFirstTowerPlaced;

// this function is called each frame /// defines the state of the game
void UpdateGameState(float deltatime);

// game state setter
void SetGameState(GameState newState);

//
// level ganarators' functions
//
#pragma region LVL_GENERATOR
void MakeRoute();						// randomly generates the route
void MakeGripPath(int numOfPoints);		// makes a grid from the generated route
void CalculatePoints(int numOfPoints);	// transfers the route to real screen coordinates
void PrepareVariables();				// prepares the varaibles before level starts (updates them to deafault state)
void SetUpLevel();						// set ups (calls all generators and randomizers) the level
#pragma endregion


//
// updates each object's state
//
#pragma region UPDATE_STATES
void UpdateTowers(float deltatime);		// updates the towers' states (cooldown; interaction;...)
void UpdateExtras(float deltatime);		// updates bullets, snowballs
void EnemyPassed(Enemy* enemy);			// is called if an enemy has reached the goal
void UpdateEnemies(float deltatime);	// updates a state of enemies
void CheckEnemiesExistance();			// check if a wave has been ended
#pragma endregion

void SpawnEnemy();						// spawns an enemy
void GameOver();						// finishes the game
#endif