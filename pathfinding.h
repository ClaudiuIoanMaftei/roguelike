///Pathfinding Functions

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

struct point
{
    int x;
    int y;
    point* next;
};

point* pointLast(point* first)
{
    if (first==NULL)
        return NULL;

    point *target;
    target=first;

    while(target->next!=NULL)
    {
        target=target->next;
    }

    return target;
}

void pointAdd(int x,int y, point **first)
{
    if(*first==NULL)
    {
        *first = new point;
        (*first)->x=x;
        (*first)->y=y;
        (*first)->next=NULL;
    }
    else
    {
        point *target;
        target=pointLast(*first);

        point *last;
        last=new point;
        last->x=x;
        last->y=y;
        last->next=NULL;
        target->next=last;
    }
}

void pointDestroy(point *first)
{
    if(first!=NULL)
    {
        pointDestroy(first->next);
        delete(first);
    }
}

bool pointSearch(int x,int y, point *first)
{
    if (first==NULL)
        return false;

    point *target;
    target=first;

    while(target!=NULL)
    {
        if ((target->x==x) and (target->y==y))
            return true;
        target=target->next;
    }

    return false;
}

bool pathExistsSearch(point *points, int entryX, int entryY, int exitX, int exitY)
{
    if (table.gridVerify("wall",entryX,entryY))
    {
        return false;
    }

    if (entryX<0 or entryY<0 or entryX>=table.width or entryY>=table.height)
        return false;

    if ((entryX==exitX) and (entryY==exitY))
        return true;

    if (pointSearch(entryX,entryY,points))
        return false;

    pointAdd(entryX,entryY,&points);

    return  pathExistsSearch(points, entryX+1, entryY, exitX, exitY) or
            pathExistsSearch(points, entryX, entryY+1, exitX, exitY) or
            pathExistsSearch(points, entryX-1, entryY, exitX, exitY) or
            pathExistsSearch(points, entryX, entryY-1, exitX, exitY);

}

bool pathExists(int entryX, int entryY, int exitX, int exitY)
{
    point* points;
    points=NULL;
    bool result=pathExistsSearch(points, entryX, entryY, exitX, exitY);
    pointDestroy(points);

    return result;
}

