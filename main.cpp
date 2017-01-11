#include "worldgen.h"
#include "player.h"

int main()
{
    table.width=60;
    table.height=60;
    worldGenerate();

    for (int index_y=0; index_y<table.height; index_y++)
    {
        for (int index_x=0; index_x<table.width; index_x++)
            if ((index_x==table.entryX) and (index_y==table.entryY)
                or(index_x==table.exitX) and (index_y==table.exitY))
               cout<<" "<<" ";
            else if (table.grid[index_y][index_x]=="wall")
                cout<<1<<" ";
            else
                cout<<0<<" ";
        cout<<endl;
    }




    return 0;
}
