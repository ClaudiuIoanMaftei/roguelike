///PlayerFunction

#ifndef included_window
#define included_window
#include "window.h"
#endif

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
    int health=5;
    int x;
    int y;
    int directionMove;
    int directionFace=DOWN;
    int difficulty=0;

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
                    if (table.gridVerify("trap",x,y))
                        health--;
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
                    if (table.gridVerify("trap",x,y))
                        health--;
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
                    if (table.gridVerify("trap",x,y))
                        health--;
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
                    if (table.gridVerify("trap",x,y))
                        health--;
                    table.gridPlace("player",x,y);
                }
                break;
            }

        }
    }

    void playerSave()
    {
        ofstream save ("player.txt");
        save<<health<<endl;
        save<<x<<endl;
        save<<y<<endl;
        save<<directionFace<<endl;
        save<<difficulty<<endl;

        save.close();
    }

    void playerLoad()
    {
        ifstream save ("player.txt");
        save>>health;
        save>>x;
        save>>y;
        save>>directionFace;
        save>>difficulty;

        save.close();
    }
}player;

