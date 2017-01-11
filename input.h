///Input Functions

#include "dependencies.h"

string direction;
direction="none";

if (_kbhit())
{
    char key = _getch();
    if (current == 'w')
        direction="up";
    if (current == 's')
        direction="down";
    if (current == 'd')
        direction="right";
    if (current == 'a')
        direction="left";
}


