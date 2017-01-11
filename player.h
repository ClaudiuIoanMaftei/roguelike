///PlayerFunction

#include "input.h"
#include "grid.h"

struct player
{
    int health;
    int x;
    int y;
    void movement ()
    {
        switch (direction)
        {
            case "up":
            {
                if (!table.gridVerify("wall",x,y-1))
                {
                    table.gridPlace("floor",x,y);
                    y=y-1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case "down":
            {
                if (!table.gridVerify("wall",x,y+1))
                {
                    table.gridPlace("floor",x,y);
                    y=y+1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case "right":
            {
                if (!table.gridVerify("wall",x+1,y))
                {
                    table.gridPlace("floor",x,y);
                    x=x+1;
                    table.gridPlace("player",x,y);
                }
                break;
            }
            case "left":
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
};

