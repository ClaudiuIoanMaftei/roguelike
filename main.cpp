#include "worldgen.h"

int main()
{
    table.width=60;
    table.height=60;
    worldGenerate();
    table.gridSave();
    return 0;
}
