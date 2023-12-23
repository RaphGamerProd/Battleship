#include "../include/boat.h"

pBoat createBoats()
{
    // Create an array of boats
    pBoat boats = malloc(sizeof(Boat) * NB_BOAT);
    if(!boats)
    {
        BOATS_NULL;
        exit(BOATS_CODE);
    }
    
    // Save the length to prevent repetition
    unsigned short length = 0;
    for(int i = 0; i < NB_BOAT; i++)
    {
        boats[i].current_direction = HORIZONTAL;
        length = rand() % BOAT_MAX_LENGTH + 1;
        boats[i].length = length;
        boats[i].x_pos = 0;
        boats[i].y_pos = 0;
    }

    return boats;
}


bool isBoatAlive(int** grid, Boat boat)
{
    if(!grid)
    {
        printf("\nThe grid is missing !\n");
    }

    unsigned short length = boat.length;
    int x_pos = boat.x_pos;
    int y_pos = boat.y_pos;

    switch(boat.current_direction)
    {
        case HORIZONTAL:
        for(int i = 0; i < length; i++)
        {
            if(grid[y_pos][x_pos + i] == BOAT)
            {
                return true;
            }
        }
        break;

        case VERTICAL:

        for(int i = 0; i < length; i++)
        {
            if(grid[y_pos + i][x_pos] == BOAT)
            {
                return true;
            }
        }
        break;

        default:
        break;
    }

    return false;

}

pBoat getCurrentBoats(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return NULL;
    }

    return Is_p_one_Turn(game) ? game->p1_boats : game->p2_boats;
}

pBoat getOpositeBoats(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return NULL;
    }
    
    return Is_p_one_Turn(game) ? game->p2_boats : game->p1_boats;
}

int numberOfBoatsLeft(int** grid, pBoat boats)
{
    if(!(grid && boats))
    {

        printf("\nBoats or grid is NULL");
        return 0;
    }

    int counter = 0;
    for(int i = 0; i < NB_BOAT; i++)
    {
        counter += isBoatAlive(grid, boats[i]);
    }

    return counter;
}
void freeBoats(pBoat boats)
{
    free(boats);
}