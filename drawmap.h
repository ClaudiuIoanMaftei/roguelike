/// Drawing Functions

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

#ifndef included_player
#define included_player
#include "player.h"
#endif

#ifndef included_window
#define included_window
#include "window.h"
#endif

#ifndef included_enemy
#define included_enemy
#include "enemy.h"
#endif

#define TILE_SIZE 64

sf::Sprite mapTile;

sf::Texture tileFloor;
sf::Texture tileWall;
sf::Texture tileWallUp;
sf::Texture tileWallUpHalf;
sf::Texture tilePlayerUp;
sf::Texture tilePlayerDown;
sf::Texture tilePlayerRight;
sf::Texture tilePlayerLeft;
sf::Texture tileSkeletonUp;
sf::Texture tileSkeletonDown;
sf::Texture tileSkeletonRight;
sf::Texture tileSkeletonLeft;
sf::Texture tileExit;
sf::Texture tileHeart;
sf::Texture tileTrap;

void textureLoad()
{
    tileFloor.loadFromFile("sprites\\sprite_floor.png");
    tileWall.loadFromFile("sprites\\sprite_wall.png");
    tileWallUp.loadFromFile("sprites\\sprite_wall_up.png");
    tileWallUpHalf.loadFromFile("sprites\\sprite_wall_up_half.png");

    tilePlayerUp.loadFromFile("sprites\\sprite_player_up.png");
    tilePlayerDown.loadFromFile("sprites\\sprite_player.png");
    tilePlayerLeft.loadFromFile("sprites\\sprite_player_left.png");
    tilePlayerRight.loadFromFile("sprites\\sprite_player_right.png");

    tileSkeletonUp.loadFromFile("sprites\\sprite_skeleton_up.png");
    tileSkeletonDown.loadFromFile("sprites\\sprite_skeleton.png");
    tileSkeletonLeft.loadFromFile("sprites\\sprite_skeleton_left.png");
    tileSkeletonRight.loadFromFile("sprites\\sprite_skeleton_right.png");

    tileExit.loadFromFile("sprites\\sprite_exit.png");
    tileHeart.loadFromFile("sprites\\spr_hearth.png");
    tileTrap.loadFromFile("sprites\\spr_trap.png");
}

void drawTile(string tile, int x, int y)
{
    if (tile=="none")
    {
        return;
    }
    else if (tile=="floor")
    {
        mapTile.setTexture(tileFloor,true);
    }
    else if (tile=="wall")
    {
        mapTile.setTexture(tileWall,true);
    }
    else if (tile=="wall_up")
    {
        mapTile.setTexture(tileWallUp,true);
    }
    else if (tile=="wall_up_half")
    {
        mapTile.setTexture(tileWallUpHalf,true);
    }
    else if (tile=="exit")
    {
        mapTile.setTexture(tileExit,true);
    }
    else if (tile=="trap")
    {
        mapTile.setTexture(tileTrap,true);
    }
    mapTile.setPosition(x*TILE_SIZE, y*TILE_SIZE);
    Window.draw(mapTile);
}

void drawHearts()
{
    mapTile.setTexture(tileHeart,true);
    for(int index=0;index<player.health;index++)
    {
        mapTile.setPosition(index*34+32, 32);
        Window.draw(mapTile);
    }
}

void drawPlayer(int x, int y)
{
    switch(player.directionFace)
    {
    case UP:
        mapTile.setTexture(tilePlayerUp, true);
        break;
    case DOWN:
        mapTile.setTexture(tilePlayerDown, true);
        break;
    case LEFT:
        mapTile.setTexture(tilePlayerLeft, true);
        break;
    case RIGHT:
        mapTile.setTexture(tilePlayerRight, true);
        break;
    }
    mapTile.setPosition(x*TILE_SIZE-32, y*TILE_SIZE-64);
    Window.draw(mapTile);
}

void drawEnemy(int face, int x, int y)
{
    switch(face)
    {
    case UP:
        mapTile.setTexture(tileSkeletonUp, true);
        break;
    case DOWN:
        mapTile.setTexture(tileSkeletonDown, true);
        break;
    case LEFT:
        mapTile.setTexture(tileSkeletonLeft, true);
        break;
    case RIGHT:
        mapTile.setTexture(tileSkeletonRight, true);
        break;
    }
    mapTile.setPosition(x*TILE_SIZE-32, y*TILE_SIZE-64);
    Window.draw(mapTile);
}

void drawMap()
{
    int viewSizeWidth=WINDOW_WIDTH/TILE_SIZE;
    int viewSizeHeight=WINDOW_HEIGHT/TILE_SIZE;
    int viewOffsetX=max(0, min(WINDOW_WIDTH-viewSizeWidth, player.x-viewSizeWidth/2));
    int viewOffsetY=max(0, min(WINDOW_HEIGHT-viewSizeHeight,player.y-viewSizeHeight/2));

    Window.clear(sf::Color(0, 0, 0));

    //Draw Grid

    for (int index_y=0; index_y<viewSizeHeight; index_y++)
        for (int index_x=0; index_x<viewSizeWidth; index_x++)
            if(table.gridVerify("player",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                drawTile("floor",index_x,index_y);
                drawPlayer(index_x,index_y);
                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up_half",index_x,index_y);
            }
            else if(table.gridVerify("enemy",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                drawTile("floor",index_x,index_y);
                drawEnemy(enemySearchFace(enemies,index_x+viewOffsetX,index_y+viewOffsetY),index_x,index_y);
                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up_half",index_x,index_y);
            }
            else if (table.gridVerify("floor",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                if ((index_x+viewOffsetX==table.exitX) and (index_y+viewOffsetY==table.exitY))
                    drawTile("exit",index_x,index_y);
                else
                    drawTile("floor",index_x,index_y);

                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up_half",index_x,index_y);
            }
            else if (table.gridVerify("trap",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                drawTile("trap",index_x,index_y);
                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up_half",index_x,index_y);
            }
            else if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up",index_x,index_y);
                else
                    drawTile("wall",index_x,index_y);
            }
            else
            {
                if (index_y+viewOffsetY>=table.height)
                    drawTile("wall",index_x,index_y);
                else
                    drawTile("wall_up",index_x,index_y);
            }

    //Draw Health
    drawHearts();

    Window.display();
}

