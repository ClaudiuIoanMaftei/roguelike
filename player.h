///PlayerFunction

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

#define NONE 0
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

struct player
{
    int health=1;
    int x;
    int y;
    int directionMove;
    int directionFace;

    void input()
    {
        directionMove=NONE;

        if (_kbhit())
        {
            char key = _getch();
            if (key == 'w')
            {
                directionMove=UP;
                directionFace=UP;
            }
            if (key == 's')
            {
                directionMove=DOWN;
                directionFace=DOWN;
            }
            if (key == 'd')
            {
                directionMove=RIGHT;
                directionFace=RIGHT;
            }
            if (key == 'a')
            {
                directionMove=LEFT;
                directionFace=LEFT;
            }
        }
    }

    void movement ()
    {
        switch (directionMove)
        {
            case UP:
            {
                if (!table.gridVerify("wall",x,y-1))
                {
                    table.gridPlace("floor",x,y);
                    y=y-1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case DOWN:
            {
                if (!table.gridVerify("wall",x,y+1))
                {
                    table.gridPlace("floor",x,y);
                    y=y+1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case RIGHT:
            {
                if (!table.gridVerify("wall",x+1,y))
                {
                    table.gridPlace("floor",x,y);
                    x=x+1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case LEFT:
            {
                if (!table.gridVerify("wall",x-1,y))
                {
                    table.gridPlace("floor",x,y);
                    x=x-1;
                    table.gridPlace("player",x,y);
                }
                break;
            }

        }
    }
}player;

