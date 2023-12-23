#include "../include/plate.h"

int** CreatePlate()
{
    // Create the rows
    int** grid = calloc(GRID_SIZE, sizeof(int*));
    if(!grid) 
    {
        GRID_NULL;
        exit(GRID_CODE);
    }

    // Create the collumns
    for(int i = 0; i < GRID_SIZE; i++)
    {
        grid[i] = calloc(GRID_SIZE, sizeof(int*));
        if(!grid[i])
        {
            GRID_NULL;
            exit(GRID_CODE);
        }
    }

    return grid;
}

int** getCurrentGrid(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return NULL;
    }
    
    return Is_p_one_Turn(game) ? game->p1_grid : game->p2_grid;
}

int** getOpositeGrid(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return NULL;
    }

    return Is_p_one_Turn(game) ? game->p2_grid : game->p1_grid;
}


void freePlate(int** plate)
{
    if(!plate)
    {
        GRID_NULL;
        return;
    }

    for(int i = 0; i < GRID_SIZE; i++)
    {
        free(plate[i]);
    }
    free(plate);
}