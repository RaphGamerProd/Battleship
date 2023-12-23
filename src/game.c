#include "../include/masterlib.h"
#include "../include/boat.h"
#include "../include/plate.h"

pGame CreateGameInstance()
{
    pGame game = malloc(sizeof(Game));
    if(!game)
    {
        ALLOCATION_ERROR;
        exit(GAME_CODE);
    }

    // Initialize base properties
    game->p1_grid = NULL;
    game->p2_grid = NULL;

    game->p1_boats = NULL;
    game->p2_boats = NULL;

    game->chosen_player = 0;
    return game;
}

int randomGridPoint()
{
    return rand() % GRID_SIZE;
}
void InitialiseGame(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }

    // Chose the starting player (Maybe I'll do it randomly)
    game->chosen_player = 0;

    // Create the boats
    game->p1_boats = createBoats();
    game->p2_boats = createBoats();

    // Create the grids
    game->p1_grid = CreatePlate();
    game->p2_grid = CreatePlate();
}

bool Is_p_one_Turn(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return false;
    }
    
    return !(game->chosen_player % 2); // Even: Player one & Odd: Player Two
}


void PlaceBoats(pGame game, bool p1Boats)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }


    int** current_grid = p1Boats ? game->p1_grid : game->p2_grid;
    pBoat current_boats = p1Boats ? game->p1_boats : game->p2_boats;
    bool is_placed = false;


    for(int i = 0; i < NB_BOAT; i++)
    {
        current_boats[i].current_direction = rand() % 2; // 0: Horizontal, 1: Vertical
        is_placed = false;
        do
        {
            // We choose an axis coordinate by hasard unil we find a spot
            // Je sais que c'est une très mauvaise façon de le faire car il se peut que ça ne trouve pas de place
            // Si j'avais un peu plus de temps je comptais faire un tableau repertoriant les case déjà occupé et faire un algo pour prendre celle qui sont libre
            // Si il y en a trop occupé pour la taille du baton j'allais tronquer la taille du tableau
            current_boats[i].y_pos = randomGridPoint();
            current_boats[i].x_pos = randomGridPoint();

            if(isTargetLocationFree(current_grid, current_boats[i]))
            {
                spawnboat(current_grid, current_boats[i]);
                is_placed = true;
            }

        } while (!is_placed);
        
    }
    
}

void spawnboat(int** grid, Boat boat)
{
    if(!grid)
    {
        printf("MISSING GRID !");
    }
    
    switch(boat.current_direction)
    {
        case HORIZONTAL:
        for(int i = 0; i < boat.length; i++)
        {
            grid[boat.y_pos][boat.x_pos + i] = BOAT;
        }
        break;

        case VERTICAL:
        for(int i = 0; i < boat.length; i++)
        {
            grid[boat.y_pos + i][boat.x_pos] = BOAT;
        }
        break;
    }
}

bool isCurrentCaseFree(int** current_grid, int pos_y, int pos_x)
{
    if(!current_grid)
    {
        GRID_NULL;
        return false;
    }

    return pos_x >= 0 && pos_x <= GRID_SIZE - 1 && pos_y >= 0 && pos_y <= GRID_SIZE - 1 && current_grid[pos_y][pos_x] == WATER;
}

bool isTargetLocationFree(int** current_grid, Boat boat)
{
    if(!(current_grid && current_grid))
    {
        printf("\nMISSING BOAT OR GRID\n");
        return false;
    }

    // Register the position in variable for quicker access
    int pos_x = boat.x_pos;
    int pos_y = boat.y_pos;

    // Check if the position is initially valid
    if(!isCurrentCaseFree(current_grid, pos_x, pos_y))
    {
        return false;
    }
    
    switch(boat.current_direction)
    {
        case HORIZONTAL:
        for(int i = 0; i < boat.length; i++)
        {
            if(!isCurrentCaseFree(current_grid, pos_y, pos_x + i)) {return false;}
        }
        break;

        case VERTICAL:
        for(int i = 0; i < boat.length; i++)
        {
            if(!isCurrentCaseFree(current_grid, pos_y + i, pos_x + i)) {return false;}
        } 
        break;
    }

    return true;
}

char getCaseVisual(case_state value)
{
    switch(value)
    {
        case WATER:
        return VI_WATER;

        case WATER_SHOT:
        return VI_WATER_SHOT;

        case BOAT:
        return VI_BOAT;

        case WRECK:
        return VI_WRECK;

        default:
        return VI_WATER;
    }
}

void printGrid(int** grid)
{
    if(!grid)
    {
        GRID_NULL;
        return;
    }

    int i;
    printf("   ");

    for(i = 0; i < GRID_SIZE; i++)
    {
        printf("  %d  ", i);
    }
    printf("\n");
    for(i = 0; i < GRID_SIZE; i++)
    {
        printf(" %d ", i);
        for(int j = 0; j < GRID_SIZE; j++)
        {
            printf("| %c |", getCaseVisual(grid[i][j]));
        }
        printf("\n");
    }
}

void enact_shoot(int** grid, int pos_x, int pos_y)
{
    if(!grid)
    {
        GRID_NULL;
        return;
    }

    grid[pos_y][pos_x] = grid[pos_y][pos_x] == WATER ? WATER_SHOT : WRECK;
    if(grid[pos_y][pos_x] == WRECK)
    {
        printf("\nTOUCHED TARGET\n");
    }

}

void shoot(pGame game, bool randomShot)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }
    
    int** opositeGrid = getOpositeGrid(game);
    if(!opositeGrid)
    {
        GRID_NULL;
        return;
    }

    // Ask the user the next grid location
    int x_pos, y_pos;

    // Select a random point on the grid
    if(randomShot)
    {
        // Pour cette façon aussi je devrais trouver un autre algorithme car non deterministe
        // Je peux potentielement looper infiniment sur une case déjà touché
        do
        {
            x_pos = randomGridPoint();
            y_pos = randomGridPoint();
        } while(opositeGrid[y_pos][x_pos] == WRECK || opositeGrid[y_pos][x_pos] == WATER_SHOT);
        
    }

    else
    {
        do
        {
            printf("\nPlease choose a row: ");
            if(scanf("%d", &y_pos) != -1)
            {
                SCAN_FIX;
            }
        }while(y_pos < 0 || y_pos > GRID_SIZE - 1);

        printf("\n");

        do
        {
            printf("\nPlease choose a collumn: ");
            if(scanf("%d", &x_pos) != -1)
            {
                SCAN_FIX;
            }
        }while(x_pos < 0 || x_pos > GRID_SIZE - 1);
    
    }

    enact_shoot(getOpositeGrid(game), x_pos, y_pos);
}


void nextGameAction(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }
    
    int answer;
    do
    {
        printf("\nWhat action would you like to do !: \n");
        printf("\n[0]: Attack the Enemie");
        printf("\n[1]: Check your plate and remaining boats informations (Careful, you'll loose a turn if so)");
        printf("\n[2]: Cheat (See the IA plate, you'll also loose a shot !)");
        printf("\n[3]: Leave Game :(");
        printf("\n===========>");

        if(scanf("%d", &answer) != -1)
        {
            SCAN_FIX;
        }

    }while(answer < 0 || answer > 3);

    switch(answer)
    {
        case 0:
        shoot(game, false);
        break;

        case 1:
            printGrid(game->p1_grid); 
            printf("\nYou have %d boats left\nThe Enemie has %d boats left\n\n",
                numberOfBoatsLeft(getCurrentGrid(game), getCurrentBoats(game)),
                numberOfBoatsLeft(getOpositeGrid(game), getOpositeBoats(game)));
        break;

        case 2:
            printGrid(game->p2_grid);
        break;
        case 3:
            freeMemory(game);
            exit(50);
        break;
    }
}


void switchPlayer(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }

    // I don't think we'll ever get to the int limit
    // At worst it'll modulo back to zero
    game->chosen_player += 1;
}

void checkWin(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }

    if(numberOfBoatsLeft(game->p1_grid, game->p1_boats) <= 0)
    {
        winGame(game, false);
        return;
    }

    else if(numberOfBoatsLeft(game->p2_grid, game->p2_boats) <= 0)
    {
        winGame(game, true);
        return;
    }
    
    return;
}

void winGame(pGame game, bool p1_win)
{
    printf("P%d Won the game thank you for playing !", !p1_win + 1);
    freeMemory(game);
    exit(50);
}

void freeMemory(pGame game)
{
    if(!game)
    {
        MISSING_GAME;
        return;
    }

    /** Free the dynamicly allocated values */
    freePlate(game->p1_grid);
    freePlate(game->p2_grid);

    free(game->p1_boats);
    free(game->p2_boats);
    /******/

    /** Free the whole game */
    free(game);
}
