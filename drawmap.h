/// Drawing Functions

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

#ifndef included_player
#define included_player
#include "player.h"
#endif

#define TILE_SIZE 64
#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 768

sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT , 32), "RogueLike");
sf::Texture tileTexture;
sf::Sprite mapTile;

void drawTile(string tile, int x, int y)
{
    if (tile=="none")
    {
        return;
    }

    tileTexture.loadFromFile("sprites\\sprite_"+tile+".png");
    mapTile.setTexture(tileTexture);
    mapTile.setPosition(x*TILE_SIZE, y*TILE_SIZE);
    Window.draw(mapTile);
}

void drawPlayer(int x, int y)
{
    tileTexture.loadFromFile("sprites\\sprite_player.png");
    mapTile.setTexture(tileTexture, true);
    mapTile.setPosition(x*TILE_SIZE-48, y*TILE_SIZE-64);
    Window.draw(mapTile);
}

void drawMap()
{
    int viewSizeWidth=WINDOW_WIDTH/TILE_SIZE;
    int viewSizeHeight=WINDOW_HEIGHT/TILE_SIZE;
    int viewOffsetX=max(0, min(WINDOW_WIDTH-viewSizeWidth, player.x-viewSizeWidth/2));
    int viewOffsetY=max(0, min(WINDOW_HEIGHT-viewSizeHeight,player.y-viewSizeHeight/2));

    while(Window.isOpen())
    {

        sf::Event Event;
        while(Window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                Window.close();
                break;
            }
        }

        Window.clear(sf::Color(0, 0, 0));

        table.gridLoad();

        //Draw Grid
        int viewPlayerX;
        int viewPlayerY;

        for (int index_y=0; index_y<viewSizeHeight; index_y++)
            for (int index_x=0; index_x<viewSizeWidth; index_x++)
                if(table.gridVerify("player",index_x+viewOffsetX,index_y+viewOffsetY))
                {
                    viewPlayerX=index_x;
                    viewPlayerY=index_y;
                    drawTile("floor",index_x,index_y);
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


        //Draw Player

        drawPlayer(viewPlayerX, viewPlayerY);

        Window.display();
    }
}
