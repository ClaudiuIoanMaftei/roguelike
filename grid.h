///Grid Functions

#include "dependencies.h"

#define MAX_HEIGHT 100
#define MAX_WIDTH 100

struct table
{
    string grid[MAX_HEIGHT][MAX_WIDTH];
    int height;
    int width;

    void gridClear(string tile)
    {
        for (int index_y=0; index_y<height; index_y++)
            for (int index_x=0; index_x<width; index_x++)
                gridPlace(tile,index_x, index_y);
    }

    void gridRectangle(string tile, int x1, int y1, int x2, int y2)
    {
        for (int index=x1; index<x2; index++)
        {
            gridPlace(tile, index, y1);
            gridPlace(tile, index, y2);
        }

        for (int index=y1; index<y2; index++)
        {
            gridPlace(tile, x1, index);
            gridPlace(tile, x2, index);
        }
    }

    void gridPlace(string tile, int x, int y)
    {
        if (x<width and x>-1 and y<height and y>-1)
            grid[y][x]=tile;
    }

    void gridFill(string tile, int x1, int y1, int x2, int y2)
    {
        for (int index_y=y1; index_y<y2; index_y++)
            for (int index_x=x1; index_x<x2; index_x++)
                gridPlace(tile,index_x, index_y);
    }

    bool gridVerify(string tile, int x, int y)
    {
        if (x<width and x>-1 and y<height and y>-1)
            return grid[y][x]==tile;
        return false;
    }

    string gridTell (int x, int y)
    {
        if (x<width and x>-1 and y<height and y>-1)
            return grid[y][x];
        string tell;
        tell="none";
        return tell;
    }

    void gridSave()
    {
        ofstream save ("grid.txt");
        save<<height<<endl;
        save<<width<<endl;

        for (int index_y=0; index_y<height; index_y++)
        {
            for (int index_x=0; index_x<width; index_x++)
                save<<grid[index_y][index_x]<<" ";
            save<<endl;
        }

        save.close();
    }

    void gridLoad()
    {
        ifstream save ("grid.txt");
        save>>height;
        save>>width;

        for (int index_y=0; index_y<height; index_y++)
        {
            for (int index_x=0; index_x<width; index_x++)
                save>>grid[index_y][index_x];
            save.get();
        }

        save.close();
    }

}table;

