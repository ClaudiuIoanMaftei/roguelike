///Enemy Functions

#include "dependencies.h"

#ifndef included_pathfinding
#define included_pathfinding
#include "pathfinding.h"
#endif

#define IDLE 0
#define FOLLOW_PLAYER 1
#define FOLLOW_EXIT 2

#define NONE 0
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

struct enemy
{
    int x;
    int y;
    int aggroRange;
    int behaviour=IDLE;
    int directionFace=DOWN;

    enemy* next;
};

enemy *enemies;

enemy* enemyLast(enemy* first)
{
    if (first==NULL)
        return NULL;

    enemy *target;
    target=first;

    while(target->next!=NULL)
    {
        target=target->next;
    }

    return target;
}

void enemyAdd(int x, int y, int aggroRange, enemy **first)
{
    if(*first==NULL)
    {
        *first = new enemy;
        (*first)->x=x;
        (*first)->y=y;
        (*first)->aggroRange=aggroRange;
        (*first)->directionFace=DOWN;
        (*first)->next=NULL;
    }
    else
    {
        enemy *target;
        target=enemyLast(*first);

        enemy *last;
        last=new enemy;
        last->x=x;
        last->y=y;
        last->aggroRange=aggroRange;
        last->directionFace=DOWN;
        last->next=NULL;
        target->next=last;
    }
}

void enemyDestroy(enemy *first)
{
    if(first!=NULL)
    {
        enemyDestroy(first->next);
        delete(first);
    }
}

int enemySearchFace(enemy *first ,int x, int y)
{
    if (first==NULL)
        return NONE;

    enemy *target;
    target=first;

    while(target!=NULL)
    {
        if ((target->x==x) and (target->y==y))
            return target->directionFace;
        target=target->next;
    }

    return NONE;
}


