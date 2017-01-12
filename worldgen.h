///Worldgen Functions

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

#ifndef included_pathfinding
#define included_pathfinding
#include "pathfinding.h"
#endif

void worldAntChange(int x, int y, int steps, int chance)
{
    string tile="floor";
    int initialChance=chance;
    for (int repeats=0; repeats<steps; repeats++)
    {
        table.gridPlace(tile,x,y);

        int changeDirection=rand()%chance;
        if (changeDirection==0)
        {
            chance=initialChance;

            changeDirection=rand()%4;
            switch(changeDirection)
            {
            case 0:
                x++;
                break;
            case 1:
                y++;
                break;
            case 2:
                x--;
                break;
            case 3:
                y--;
                break;
            }

            if (x<0)
                x=0;
            if (y<0)
                y=0;

            if (x>=table.width)
                x=table.width-1;
            if (y>=table.height)
                y=table.height-1;
        }
        else
            chance--;
    }
}

void worldGenerate()
{
    srand(time(NULL));

    string tile;
    tile="wall";
    table.gridClear(tile);
    int table_size=(table.height+table.width)/2;

    for (int repeats=0; repeats<table_size/5; repeats++)
    {
        int room_x=rand()%table.width;
        int room_y=rand()%table.height;
        int room_size_min=1+table_size/15;
        int room_height=rand()%room_size_min + table_size/10;
        int room_width=rand()%room_size_min + table_size/10;

        tile="floor";
        table.gridFill(tile, room_x, room_y, room_x+room_width, room_y+room_height);

        worldAntChange(room_x+room_width/2, room_y+room_width/2, table_size*4, 1);
        worldAntChange(room_x+room_width/2, room_y+room_width/2, table_size*6, table_size/4);
    }

    tile="wall";
    table.gridRectangle(tile, 0, 0, table.width-1, table.height-1);

    do
    {
        table.entryX=rand()%table.width;
        table.entryY=rand()%table.height;
        table.exitX=rand()%table.width;
        table.exitY=rand()%table.height;
    }
    while(!pathExists(table.entryX, table.entryY, table.exitX, table.exitY));
}
