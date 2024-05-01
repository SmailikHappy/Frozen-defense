#include "gamehandler.h"
#include <algorithm>
#include <time.h>

// counts a number of spawned enemies
unsigned short numberOfEnemiesSpawned;
// counts a delay between each enemy spawn
float passedTime;
// counts a delay between wave spawn
float passedTimeBeforeEnemies;

// variables for path generation, contains alrady used parts of playfield
bool thisVertPartIsUsed[NUMBER_OF_FIELD_PARTS_VERT];
bool thisHorizPartIsUsed[NUMBER_OF_FIELD_PARTS_HORIZ];

// is responnsible of actual game beginning
bool isFirstTowerPlaced;

// calculates the number of path points (that points must be reached)
unsigned char maxPoints = std::min(std::min(NUMBER_OF_FIELD_PARTS_VERT, NUMBER_OF_FIELD_PARTS_HORIZ), NUMBER_OF_COLUMNS / 2);

// structure for "fantom" point-coordinates
struct Point {
	unsigned short x;
	unsigned short y;
};

// varaibles which will contain screen coordinates (for enemies) and "fantom" grid-coordinates
Tmpl8::vec2 routePointsPos[std::min(NUMBER_OF_FIELD_PARTS_VERT, NUMBER_OF_FIELD_PARTS_HORIZ) + 1];
Point routePoints[std::min(NUMBER_OF_FIELD_PARTS_VERT, NUMBER_OF_FIELD_PARTS_HORIZ) + 1];
// position of enemy's spawn
Tmpl8::vec2 spawnEnemyPos;

// array with enemies
Enemy enemies[20];
// type of enemy, which is used in a present wave (responds to enemies' traits)
int presentType;

void UpdateGameState(float deltatime)
{
	// defines the actual game state
	switch (presentGameState)
	{
		case GameState::WaitingForWaveEnd:		// Game waits until all enemies will be disappeared / killed
			UpdateTowers(deltatime);
			UpdateExtras(deltatime);
			UpdateEnemies(deltatime);
			CheckEnemiesExistance();
			break;

		case GameState::SpawningEnemies:		// Game spawns enemies
			if (passedTime < milSecsToWaitForTheNextEnemy) passedTime += deltatime; // if the cooldown between enemies was passed -> spawn a new one
			else {
				SpawnEnemy();
				numberOfEnemiesSpawned++;
				passedTime = 0.0f;
			}

			if (numberOfEnemiesSpawned == enemysType[presentType].numberToSpawn) {	// if there is enough spawned enemies, switches the game state to the next
				SetGameState(GameState::WaitingForWaveEnd);
			}

			UpdateTowers(deltatime);
			UpdateExtras(deltatime);
			UpdateEnemies(deltatime);
			break;

		case GameState::WaitingForCooldown:		// Game waits when a cooldown finished
			passedTimeBeforeEnemies += deltatime / timeKoef;			// counts the cooldown
			UpdateExtras(deltatime);

			if (passedTimeBeforeEnemies >= milSecsToWaitBeforeWave)		// if cooldown passed, switch the game state to next one
			{
				SetGameState(GameState::SpawningEnemies);
				ChangeMainInfo(&wave, 1);
			}
			break;

		case GameState::WaitingForFirstTower:	// Game waits for the first placed tower in game
			if (!isFirstTowerPlaced) return;
			else {
				SetGameState(GameState::WaitingForCooldown);
			}
			break;

		case GameState::Loading:				// Game loads the level
			SetUpLevel();
			PrepareVariables();
			MakeRoute();
			MakeGripPath(maxPoints + 1);

			routePoints[maxPoints].x += 2;		// stretches the last coordinate for future calculations

			CalculatePoints(maxPoints + 1);

			spawnEnemyPos = { -50, (float)routePointsPos[0].y };		// sets enemy's spawnpoint
			leftPathY = (unsigned short) routePointsPos[0].y;			// sets screen coordinates of start-path to draw it
			rightPathY = (unsigned short) routePointsPos[maxPoints].y;	// sets screen coordinates of finish path (igloo) to draw it

			GenerateAmbienceInPlayZone(leftPathY, rightPathY);			// clears extra ambient objects (trees / lakes) to draw them only as a background

			SetGameState(GameState::WaitingForFirstTower);				// sets the game un a waiting time
			break;

		case GameState::Null:					// It is not an active playzone
			SetGameState(GameState::Loading);							// load the game
			break;
	}
}

void SetGameState(GameState newState)
{
	//BeginGameState(presentGameState, newState);
	//EndGameState(presentGameState, newState);

	if (newState == GameState::WaitingForCooldown)
	{
		passedTimeBeforeEnemies = 0.0f;

		if (presentGameState == GameState::WaitingForWaveEnd)
		{
			numberOfEnemiesSpawned = 0;
			passedTime = milSecsToWaitForTheNextEnemy;
			
			if (wave.quan < 10) presentType = rand() % 2;
			else presentType = rand() % NUMBER_OF_ENEMYS_TYPE;
		}
	}

	presentGameState = newState;
}


#pragma region LVL_GENERATOR
void SetUpLevel() // Prepares variables, sets the deafault values
{
	wave.quan = 0;
	castleHP.quan = 20;
	gold.quan = 1000;

	numberOfEnemiesSpawned = 0;
	isFirstTowerPlaced = false;
	passedTime = milSecsToWaitForTheNextEnemy;

	tPanel.HideInfo(); // hides the info panel

	presentType = 0;
	numberOfEnemiesSpawned = 0;

	doneDamage = 0.0f;
	spendGold = 0;
}

void PrepareVariables() // Also prepares all global variables before a level starts, sets the deafault values
{
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++){
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			pathGridBool[i][j] = false;
			pathGridShort[i][j] = 0;
		}
	}

	for (int i = 0; i < NUMBER_OF_FIELD_PARTS_HORIZ; i++){
		thisHorizPartIsUsed[i] = false;
	}

	for (int i = 0; i < NUMBER_OF_FIELD_PARTS_VERT; i++){
		thisVertPartIsUsed[i] = false;
	}

	for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++){
		enemies[i].isAlive = false;
	}

	for (int i = 0; i < NUMBER_OF_ROWS * NUMBER_OF_COLUMNS; i++){
		delete towers[i];
		towers[i] = nullptr;
	}

	stoneBullets.clear();
	snowBalls.clear();
	ambiencePZ.clear();
}

void MakeRoute() // Generates the path
{
	// randomize the seed
	srand((unsigned int)time(NULL));

	unsigned short finishY = rand() % NUMBER_OF_ROWS; // Y level of finish

	// Generates restricted number of path points on exact parts of the playfield
	for (int i = 0; i < maxPoints; i++)
	{
		// Randomize
		unsigned short randX = 1 + (rand() % (NUMBER_OF_ROWS - 2));
		unsigned short randY = rand() % NUMBER_OF_COLUMNS;

		// Check if these locations are busy
		if (thisHorizPartIsUsed[randX * NUMBER_OF_FIELD_PARTS_HORIZ / NUMBER_OF_COLUMNS] ||
			thisVertPartIsUsed[randY * NUMBER_OF_FIELD_PARTS_VERT / NUMBER_OF_ROWS] ||
			randY == finishY)
		{	 // if is busy >>> rerandomize
			i--; continue;
		}
		else // They are not >>> add them
		{
			thisHorizPartIsUsed[randX * NUMBER_OF_FIELD_PARTS_HORIZ / NUMBER_OF_COLUMNS] = true;
			thisVertPartIsUsed[randY * NUMBER_OF_FIELD_PARTS_VERT / NUMBER_OF_ROWS] = true;

			routePoints[i] = { randX, randY };
		}
	}
	// Adds a "finish" point for visual generator
	routePoints[maxPoints] = { NUMBER_OF_COLUMNS - 1, finishY };
}

void MakeGripPath(int numOfPoints) // Draws the path for rendering
{
	int i = 0;
	Point activePoint = { 0, routePoints[0].y };								// sets the start point
	pathGridBool[(int)routePoints[0].y][0] = true;								// cell becomes busy (will not allow to place a tower there)
	pathGridShort[(int)routePoints[0].y][0] = 2;								// 

	while (i < numOfPoints)
	{
		if (activePoint.y != routePoints[i].y)									// point was moved on Y coord
		{
			if (activePoint.y > routePoints[i].y) {								// if under
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 4;		// previous point increases by 4
				activePoint.y--;												// go to next
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 1;		// next point increases by 1
			}
			else
			{																	// if above
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 1;		// previous point increases by 1
				activePoint.y++;												// go to next
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 4;		// next point increases by 4
			}
			pathGridBool[(int)activePoint.y][(int)activePoint.x] = true;

		}
		else if (activePoint.x != routePoints[i].x)								// point was moved on X coord
		{
			if (activePoint.x > routePoints[i].x) {								// if on right
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 2;		// previous point increases by 2
				activePoint.x--;												// go to next
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 8;		// next point increases by 8
			}
			else
			{																	// if on left
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 8;		// previous point increases by 8
				activePoint.x++;												// go to next
				pathGridShort[(int)activePoint.y][(int)activePoint.x] += 2;		// next point increases by 2
			}
			pathGridBool[(int)activePoint.y][(int)activePoint.x] = true;		// sets new point as busy
		}
		else
		{
			i++;					// go to next target point
		}
	}

	pathGridShort[(int)activePoint.y][(int)activePoint.x] += 8;					// increases the last point by 8 
}

void CalculatePoints(int numOfPoints) // Calculates the screen pixel position for enemies future calculations
{
	for (int i = 0; i < numOfPoints; i++)
	{
		routePointsPos[i] = {
			routePoints[i].x * cellEdge + PLAYFIELD_L_BORDER + cellEdge / 2, // transfer formula
			routePoints[i].y * cellEdge + PLAYFIELD_L_BORDER + cellEdge / 2
		};
	}
}
#pragma endregion

#pragma region UPDATE_STATES
void UpdateEnemies(float deltatime) // Updates enemies' position
{
	for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++)
	{
		if (enemies[i].isAlive)
		{
			// number of pointers to make code readable and optimized
			unsigned short* indexOfRoutePointCoordsToReach = &enemies[i].routePointToReach;

			float* routePointToReachY = &routePointsPos[*indexOfRoutePointCoordsToReach].y;
			float* routePointToReachX = &routePointsPos[*indexOfRoutePointCoordsToReach].x;

			float* enemysPosY = &enemies[i].position.y;
			float* enemysPosX = &enemies[i].position.x;

			char* enemysDirectionY = &enemies[i].directionY;
			char* enemysDirectionX = &enemies[i].directionX;

			// defines the position of enemy towards 'route point' and calcs the movement
			if ((*enemysPosY) != (*routePointToReachY))	// by Y coordinate (firstly)
			{
				if ((*enemysPosY) < (*routePointToReachY) && (*enemysDirectionY) == 1)
				{
					// NOTHING TO CHANGE
				}
				else if ((*enemysPosY) > (*routePointToReachY) && (*enemysDirectionY) == 1)
				{
					(*enemysPosY) = (*routePointToReachY);
					(*enemysDirectionY) = 0;

					if ((*enemysPosX) > (*routePointToReachX)) (*enemysDirectionX) = -1;
					else (*enemysDirectionX) = 1;
				}
				else if ((*enemysPosY) > (*routePointToReachY) && (*enemysDirectionY) == -1)
				{
					// NOTHING TO CHANGE
				}
				else
				{
					(*enemysPosY) = (*routePointToReachY);
					(*enemysDirectionY) = 0;

					if ((*enemysPosX) > (*routePointToReachX)) (*enemysDirectionX) = -1;
					else (*enemysDirectionX) = 1;
				}
			}
			else if ((*enemysPosX) != (*routePointToReachX)) // by X coordinate (secondly)
			{
				if ((*enemysPosX) < (*routePointToReachX) && (*enemysDirectionX) == 1)
				{
					// NOTHING TO CHANGE
				}
				else if ((*enemysPosX) > (*routePointToReachX) && (*enemysDirectionX) == 1)
				{
					(*enemysPosX) = (*routePointToReachX);
					(*enemysDirectionX) = 0;

					enemies[i].routePointToReach++;
					if ((*enemysPosY) > routePointsPos[*indexOfRoutePointCoordsToReach].y) (*enemysDirectionY) = -1; // WHY ERROR IF (*routePointToReach) IS PLACED??????
					else (*enemysDirectionY) = 1;
				}
				else if ((*enemysPosX) > (*routePointToReachX) && (*enemysDirectionX) == -1)
				{
					// NOTHING TO CHANGE
				}
				else	// if route point has been reached
				{
					(*enemysPosX) = (*routePointToReachX);
					(*enemysDirectionX) = 0;

					enemies[i].routePointToReach++;
					if ((*enemysPosY) > routePointsPos[*indexOfRoutePointCoordsToReach].y) (*enemysDirectionY) = -1; // WHY ERROR IF (*routePointToReach) IS PLACED??????
					else (*enemysDirectionY) = 1;
				}
			}

			(*enemysPosX) += enemies[i].speedKoef * cellEdge * (*enemysDirectionX) * enemies[i].speed * deltatime / 1000;
			(*enemysPosY) += enemies[i].speedKoef * cellEdge * (*enemysDirectionY) * enemies[i].speed * deltatime / 1000;

			enemies[i].speedKoef = 1.0f;


			if ((*enemysPosX) >= PLAYFIELD_R_BORDER + cellEdge) // if an enemy has reached the "castle"
			{
				EnemyPassed(&enemies[i]);
			}
		}
	}
}

void EnemyPassed(Enemy* enemy) // Function is called when enemy reaches the castle
{
	ChangeMainInfo(&castleHP, -enemy->castledamage);
	enemy->isAlive = false;

	if (castleHP.quan <= 0) GameOver();
}

void CheckEnemiesExistance() // Check if enemies are alive at all
{
	for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++)
	{
		if (enemies[i].isAlive) return;
	}
	SetGameState(GameState::WaitingForCooldown);
}

void UpdateTowers(float deltatime) // Updates towers' states every frame
{
	// Checks each tile with or without tower
	for (Tower* tower : towers)
	{
		if (!tower) continue;								// If no tower >>> skip
		if (!tower->isActive) continue;						// If not active >>> skip

		if (enemysType[presentType].resistance == tower->towerelement) continue;	// If the wave is resistant to exact tower_type >>> skip because tower must not shoot

		if (tower->timePassed >= tower->cooldown) {			// If tower's cooldown is passed

			vector<Enemy*> triggeredEnemies;				// Array with all enemies in a radius of a tower

			for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++) // Check every enemy
			{
				if (!enemies[i].isAlive) continue;			// If already dead >>> skip

				if ((enemies[i].position.x - tower->position.x) * (enemies[i].position.x - tower->position.x) +
					(enemies[i].position.y - tower->position.y) * (enemies[i].position.y - tower->position.y) <= tower->radius * tower->radius)
				{											// If the enemy is in a tower's radius >>> push to array
					triggeredEnemies.push_back(&enemies[i]);
				}
			}
			if (triggeredEnemies.size() == 0) continue;		// If no enemies were triggered >>> skip

			tower->Shoot(triggeredEnemies);					// Tower shoots
			tower->timePassed = 0.0f;						// Updates tower's cooldown
		}
		else
			tower->timePassed += deltatime;					// Add miliseconds tower awaiting
	}
}

void UpdateExtras(float deltatime) // Updates any extras
{
	// lists bullets (of 'stone' tower)
	for (auto it = stoneBullets.begin(); it != stoneBullets.end(); )
	{
		auto bullet = *it;

		// difference between tyarget and bullet
		float dx = bullet->target->position.x - bullet->position.x;
		float dy = bullet->target->position.y - bullet->position.y;

		// if they reached
		if (dx * dx + dy * dy <= bullet->speed * bullet->speed * deltatime * deltatime / 1000000.0f) {
			it = stoneBullets.erase(it);
			bullet->Hit();
			delete bullet;
			continue;
		}
		else
		{
			it++;
		}

		// calcs the movement of bullet
		float s_partial = bullet->speed / (float) sqrt(dx * dx + dy * dy);

		// adds the reasult of the move
		bullet->position.x += s_partial * dx * deltatime / 1000.0f;
		bullet->position.y += s_partial * dy * deltatime / 1000.0f;
	}

	// lists snowballs (of 'snow' tower)
	for (auto it = snowBalls.begin(); it != snowBalls.end(); )
	{
		auto ball = *it;

		// difference between tyarget and bullet
		float dx = ball->targetPos.x - ball->position.x;
		float dy = ball->targetPos.y - ball->position.y;

		// if snowball has reached the target point
		if (dx * dx + dy * dy <= ball->speed * ball->speed * deltatime * deltatime / 1000000.0f)
		{
			vector<Enemy*> triggeredEnemies;

			for (int i = 0; i < MAX_NUMBER_OF_ENEMIES; i++)
			{
				if (!enemies[i].isAlive) continue;

				// if the explosion triggers an enemy
				if ((enemies[i].position.x - ball->position.x) * (enemies[i].position.x - ball->position.x) + (enemies[i].position.y - ball->position.y) * (enemies[i].position.y - ball->position.y) <= ball->radius * ball->radius)
				{
					triggeredEnemies.push_back(&enemies[i]);
				}
			}
			// explode and delete the snowball
			it = snowBalls.erase(it);
			ball->Explode(triggeredEnemies);
			delete ball;
			continue;
		}
		else
		{
			it++;
		}

		// calc a speed
		float s_partial = ball->speed / (float) sqrt(dx * dx + dy * dy);
		
		// add a move
		ball->position.x += s_partial * dx * deltatime / 1000.0f;
		ball->position.y += s_partial * dy * deltatime / 1000.0f;
	}
}
#pragma endregion

void SpawnEnemy() // Spawns an enemy
{
	Enemy enemy(&enemysType[presentType], wave.quan);
	enemies[numberOfEnemiesSpawned] = enemy;
}

void GameOver()	  // game over
{
	LoadGameOverInfo();
	Blend(screen_, 0xffffff, 1.0f, 0, 0, 800, 800);
	presentScene = Scenes::gameover;
}