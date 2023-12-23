#include "include/masterlib.h"
#include "include/boat.h"
#include "include/plate.h"


void main()
{
    // Seed initialisation
    srand(time(NULL));

    // Create the game instance
    pGame game = CreateGameInstance();
    // Initialise its base properties
    InitialiseGame(game);

    // Place the boats through the grids
    PlaceBoats(game, true);
    PlaceBoats(game, false);

    // Main game loop
    do 
    {
        nextGameAction(game);
        switchPlayer(game);
        for(int i = 0; i < 1; i++){shoot(game, true);}
        switchPlayer(game);
        checkWin(game);
    }while(true);

    freeMemory(game);
}