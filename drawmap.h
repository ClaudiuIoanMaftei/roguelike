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

#define TILE_SIZE 64



sf::Sprite mapTile;

sf::Texture tileFloor;
sf::Texture tileWall;
sf::Texture tileWallUp;
sf::Texture tileWallUpHalf;
sf::Texture tilePlayer;

void textureLoad()
{
    tileFloor.loadFromFile("sprites\\sprite_floor.png");
    tileWall.loadFromFile("sprites\\sprite_wall.png");
    tileWallUp.loadFromFile("sprites\\sprite_wall_up.png");
    tileWallUpHalf.loadFromFile("sprites\\sprite_wall_up_half.png");
    tilePlayer.loadFromFile("sprites\\sprite_player.png");
}

void drawTile(string tile, int x, int y)
{
    if (tile=="none")
    {
        return;
    }
    else if (tile=="floor")
    {
        mapTile.setTexture(tileFloor);
    }
    else if (tile=="wall")
    {
        mapTile.setTexture(tileWall);
    }
    else if (tile=="wall_up")
    {
        mapTile.setTexture(tileWallUp);
    }
    else if (tile=="wall_up_half")
    {
        mapTile.setTexture(tileWallUpHalf);
    }

    mapTile.setPosition(x*TILE_SIZE, y*TILE_SIZE);
    Window.draw(mapTile);
}

void drawPlayer(int x, int y)
{
    mapTile.setTexture(tilePlayer, true);
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

    for (int index_y=0; index_y<viewSizeHeight; index_y++)
        for (int index_x=0; index_x<viewSizeWidth; index_x++)
            if(table.gridVerify("player",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                drawTile("floor",index_x,index_y);
                drawPlayer(index_x,index_y);
                if (table.gridVerify("wall",index_x+viewOffsetX,index_y+viewOffsetY+1))
                    drawTile("wall_up_half",index_x,index_y);
            }
            else if (table.gridVerify("floor",index_x+viewOffsetX,index_y+viewOffsetY))
            {
                drawTile("floor",index_x,index_y);
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


    Window.display();
}

