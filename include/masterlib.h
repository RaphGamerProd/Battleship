/** Contain all the game main informations */
#ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/** @brief The length of the grill */
#define GRID_SIZE 10
/** @brief The max number of boat */
#define NB_BOAT 5
/** @brief Boat max length */
#define BOAT_MAX_LENGTH 5
/** Boot fail security */
#define BOOT_FAIL exit(10)
/* Small hack to prevent scanf infinite loop if wrong type entered */
#define SCAN_FIX scanf("%*[^\n]")

/** Small verification before booting the game */
/**
#if GRID_SIZE < 10
    printf("\nGRID_SIZE MUST BE GREATER THAN 10 !\n");
    BOOT_FAIL;
#endif

#if BOAT_MAX_LENGTH > GRID_SIZE || BOAT_MAX_LENGTH == 0
    printf("\nBOAT SIZE IS LONGER THAN GRID SIZE  OR BOAT LENGTH IS NULL !\n");
    BOOT_FAIL;

#if NB_BOAT < 1
    printf("NB_BOATS CANNOT BE NULL");
    exit
#endif
/********/

/** @brief Allocation error message */
#define ALLOCATION_ERROR printf("\nALLOCATION ERROR !\n")
/** Missing game */
#define MISSING_GAME printf("\nMISSING GAME INSTANCE !\n")
/** Game allocation error code */
#define GAME_CODE 1

/** How the case visuals */
#define VI_BOAT '@'
#define VI_WATER ' '
#define VI_WATER_SHOT '#'
#define VI_WRECK 'X'



/* Diffrents enumarations */
/** The current state of a case */
typedef enum  {WATER, WATER_SHOT, BOAT, WRECK}case_state;
/** The current direction of the boat */
typedef enum  {HORIZONTAL, VERTICAL}direction;


/**
 * @brief The structure of a single boat
 * @param current_direction The desired direction of the boat when constructed
 * @param x_pos The lateral position in the grid
 * @param y_pos The up direction in the grid
 * @param lentgh The length of the boat
 * @param body An array of int to check if the part of the boat
 * 
 */
typedef struct
{
    direction current_direction;
    bool isDestroyed;
    int x_pos;
    int y_pos;
    unsigned short length;
    unsigned short currentNumberofBoats;
}Boat;
/** Small type definition for better understanding */
typedef Boat* pBoat;
/**
 * @brief The structure of the whole game
 * @param p1_grid Player_1's grid
 * @param p2_grid Player_2's grid
 * @param p1_boats Player_1's boats
 * @param p2_boats Player_2's boats
 * @param chosen_player If even return p1, else, return p2
 */
typedef struct
{
    int chosen_player;
    int** p1_grid;
    int** p2_grid;
    pBoat p1_boats;
    pBoat p2_boats;
    
}Game;
/** @brief Small type definition for better understanding */
typedef Game* pGame;

/** Create the current game */
pGame CreateGameInstance();

/** Initialise the game base values (Such as creating player's grids, boats etc)*/
void InitialiseGame(pGame game);
/** Function that free memory from all the previous allocation*/
void freeMemory(pGame game);
/** Place all the boats in the game 
 * @param p1Boats If true spawn P1 boats else spawn P2 boats
*/
void PlaceBoats(pGame game, bool p1Boats);
/** Spawn a single boat in a direction */
void spawnboat(int** grid, Boat boat);
/** Prints out a single grid */
void printGrid(int** grid);
/** Shoot to a boat a check if a boat is destroyed if there's no more boat Player_i wins */
void shoot(pGame game, bool randomShot);
/** Shoot at a certain grid location */
void enact_shoot(int** grid, int pos_x, int pos_y);
/** Print winner and terminate the game
 * @param p1_win If P1 won the game else it'll be P2
*/
void winGame(pGame game, bool p1_win);
/** Let the player choose the next game action */
void nextGameAction(pGame game);
/** Change player*/
void switchPlayer(pGame game);
/** Check if there's a winner and call win function if so */
void checkWin(pGame game);

/** Return if the current player is the player one*/
bool Is_p_one_Turn(pGame game);
/** Check iof the current case is WATER */
bool isCurrentCaseFree(int** current_grid, int pos_y, int pos_x);
/** Predict if the boat is able to spawn in this direction */
bool isTargetLocationFree(int** current_grid, Boat boat);
/** Return a special character in function of the value of the case */
char getCaseVisual(case_state value);

// Return a number between 0 and GRID_SIZE - 1
int randomGridPoint();

#endif