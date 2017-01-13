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

void pointDeleteLast(point *first)
{
    if(first!=NULL)
    {
        point *target;
        target=first;

        while(target->next->next!=NULL)
            target=target->next;
        delete(target->next);
        target->next=NULL;
    }
}

void pointDelete(point *first, int x, int y)
{
    if(first!=NULL)
    {
        point *prev;
        prev=first;
        point *target;
        target=first->next;

        if (prev->x==x and prev->y==y)
        {
            delete(prev);
            if (target!=NULL)
                *(first)=*target;
            else
                first=NULL;
            return;
        }

        while(target!=NULL)
        {
            if (target->x==x and target->y==y)
            {
                prev->next=target->next;
                delete(target);
                return;
            }
            target=target->next;
            prev=prev->next;
        }
    }
}

void pointShow(point *first)
{
    point *target;
    target=first;
    while(target!=NULL)
    {
        cout<<target->x<<" "<<target->y<<endl;
        target=target->next;
    }
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
/*   ~~Si Dumnezeu in prima zi a facut lumina, da' nu poate sa faca codul asta sa mearga
point* pathFind(int entryX, int entryY, int exitX, int exitY)
{

    point* toVisit;
    toVisit=NULL;
    pointAdd(entryX,entryY,&toVisit);

    int distance[table.width][table.height];
    for(int index_y=0; index_y<table.height; index_y++)
        for(int index_x=0; index_x<table.width; index_x++)
            distance[index_x][index_y]=-1;
    distance[entryX][entryY]=0;

    while(toVisit!=NULL and !pointSearch(exitX,exitY,toVisit))
    {
        int targetX=pointLast(toVisit)->x;
        int targetY=pointLast(toVisit)->y;

        pointDelete(toVisit,targetX,targetY);

        if(table.gridVerify("floor",targetX+1,targetY))
           if (distance[targetX+1][targetY]<0)
        {
            pointAdd(targetX+1,targetY,&toVisit);
            distance[targetX+1][targetY]=distance[targetX][targetY]+1;
        }
        if(table.gridVerify("floor",targetX-1,targetY))
           if (distance[targetX-1][targetY]<0)
        {
            pointAdd(targetX-1,targetY,&toVisit);
            distance[targetX-1][targetY]=distance[targetX][targetY]+1;
        }
        if(table.gridVerify("floor",targetX,targetY+1))
           if (distance[targetX][targetY+1]<0)
        {
            pointAdd(targetX,targetY+1,&toVisit);
            distance[targetX][targetY+1]=distance[targetX][targetY]+1;
        }
        if(table.gridVerify("floor",targetX,targetY-1))
           if(distance[targetX][targetY-1]<0)
        {
            pointAdd(targetX,targetY-1,&toVisit);
            distance[targetX][targetY-1]=distance[targetX][targetY]+1;
        }
    }

    for(int index_y=0; index_y<table.height; index_y++)
        {
            for(int index_x=0; index_x<table.width; index_x++)
                if (distance[index_x][index_y]==-1)
                    cout<<" ";
                else
                    cout<<distance[index_x][index_y];
            cout<<endl;
        }
        cout<<endl;

    pointDestroy(toVisit);

    point* path;
    path=NULL;

    while(exitX!=entryX and exitY!=entryY)
    {
        pointAdd(exitY,exitX,&path);
        if (distance[exitX+1][exitY]<distance[exitX][exitY] and distance[exitX+1][exitY]!=-1)
            exitX++;
        else if (distance[exitX-1][exitY]<distance[exitX][exitY] and distance[exitX-1][exitY]!=-1)
            exitX--;
        else if (distance[exitX][exitY+1]<distance[exitX][exitY] and distance[exitX][exitY+1]!=-1)
            exitY++;
        else if (distance[exitX][exitY-1]<distance[exitX][exitY] and distance[exitX][exitY-1]!=-1)
            exitY--;
    }

    return path;
}
*/
