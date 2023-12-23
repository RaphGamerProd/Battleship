#ifndef PLATE_H
#define PLATE_H

#include "masterlib.h"

/** Some constant to help  with pointers null check */
#define GRID_NULL printf("\nThe grid is null\n")
/** Game allocation error code */
#define GRID_CODE 3

/** Create a singular grid for a players */
int** CreatePlate();
/** Returns the curreent grid in function of the player */
int** getCurrentGrid(pGame game);
/** Returns the grid of the relative enemie player */
int** getOpositeGrid(pGame game);

/** Check if the player has any boats left */
bool AnyBoatLeft(int** grid);

/** Free a plate array from memorty */
void freePlate(int** plate);

#endif