#ifndef BOAT_H
#define BOAT_H

#include <stdlib.h>
#include "masterlib.h"

/** Constants to help  with pointers null check */
#define BOATS_NULL printf("\nThe boat is null\n")
/** Boat allocation error code */
#define BOATS_CODE 2

/** Function that create an array of boats for a player /!\ Note that this boat will have a random length */
pBoat createBoats();
/** Retrieve the currrent set of boats */
pBoat getCurrentBoats(pGame game);
/** Retrieve the enimies boays */
pBoat getOpositeBoats(pGame game);

/** Check wether or not a boat is alive */
bool isBoatAlive(int** grid, Boat boat);

/** Check the number of boats left */
int numberOfBoatsLeft(int** grid, pBoat boats);

#endif