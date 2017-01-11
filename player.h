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
        }
    }
};

