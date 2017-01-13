///Enemy Functions

#include "dependencies.h"

#ifndef included_pathfinding
#define included_pathfinding
#include "pathfinding.h"
#endif

#ifndef included_player
#define included_player
#include "player.h"
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
    int aggroRange=5+player.difficulty/2;
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

int enemySearchFace(enemy *first,int x, int y)
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

void enemySave()
{
    ofstream save ("enemy.txt");

    if (enemies==NULL)
        return;

    enemy *target;
    target=enemies;

    save<<target->aggroRange;
    save<<target->behaviour;
    save<<target->directionFace;
    save<<target->x;
    save<<target->y;

    while(target->next!=NULL)
    {
        target=target->next;
        save<<target->aggroRange;
        save<<target->behaviour;
        save<<target->directionFace;
        save<<target->x;
        save<<target->y;
    }

    save.close();
}

void enemyLoad()
{
    ifstream save ("enemy.txt");

    do
    {
        int aggroRange;
        int behaviour;
        int directionFace;
        int x;
        int y;

        save>>aggroRange;
        save>>behaviour;
        save>>directionFace;
        save>>x;
        save>>y;

        enemyAdd(x,y,aggroRange,&enemies);
        table.gridPlace("enemy",x,y);
    }
    while(!save.eof());

    save.close();
}

void enemyMove(enemy *enemy)
{
    //if (abs(player.x-enemy->x)<enemy->aggroRange and abs(player.y-enemy->y)<enemy->aggroRange)
    {
        if (player.x<enemy->x)
        {
            if(table.gridVerify("floor",enemy->x-1,enemy->y))
            {
                table.gridPlace("floor",enemy->x,enemy->y);
                enemy->x--;
                table.gridPlace("enemy",enemy->x,enemy->y);
                enemy->directionFace=LEFT;
            }
        }
        else if (player.x>enemy->x)
        {
            if (table.gridVerify("floor",enemy->x+1,enemy->y))
            {
                table.gridPlace("floor",enemy->x,enemy->y);
                enemy->x++;
                table.gridPlace("enemy",enemy->x,enemy->y);
                enemy->directionFace=RIGHT;
            }
        }
        else if (player.y>enemy->y)
        {
            if(table.gridVerify("floor",enemy->x,enemy->y+1))
            {
                table.gridPlace("floor",enemy->x,enemy->y);
                enemy->y++;
                table.gridPlace("enemy",enemy->x,enemy->y);
                enemy->directionFace=DOWN;
            }
        }
        else if (player.y<enemy->y)
        {
            if(table.gridVerify("floor",enemy->x,enemy->y-1))
            {
                table.gridPlace("floor",enemy->x,enemy->y);
                enemy->y--;
                table.gridPlace("enemy",enemy->x,enemy->y);
                enemy->directionFace=UP;
            }
        }
        if (abs(player.x-enemy->x)<2 and abs(player.y-enemy->y)<2)
            player.health--;
    }
}

