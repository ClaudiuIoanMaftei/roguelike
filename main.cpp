#include "worldgen.h"

#ifndef included_player
#define included_player
#include "player.h"
#endif

#ifndef included_drawmap
#define included_drawmap
#include "drawmap.h"
#endif

int main()
{
    //Initialize Level
    table.width=60;
    table.height=60;
    worldGenerate();
    table.gridSave();
    player.playerSave();

    textureLoad();

    point* points;
    points=NULL;
    points= pathFind(player.x, player.y,table.exitX,table.exitY);
    pointShow(points);



    //Main Action
    while(Window.isOpen())
    {
        player.directionMove=NONE;
        //Able to close window
        sf::Event Event;
        while(Window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                Window.close();
                break;
            //Player Move
            case sf::Event::KeyPressed:
                switch(Event.key.code)
                {
                case sf::Keyboard::A:
                    player.directionMove=LEFT;
                    player.directionFace=LEFT;
                    break;
                case sf::Keyboard::D:
                    player.directionMove=RIGHT;
                    player.directionFace=RIGHT;
                    break;
                case sf::Keyboard::W:
                    player.directionMove=UP;
                    player.directionFace=UP;
                    break;
                case sf::Keyboard::S:
                    player.directionMove=DOWN;
                    player.directionFace=DOWN;
                    break;
                case sf::Keyboard::Escape:
                    Window.close();
                    break;
                }


            }
        }
        //Move
        if (player.directionMove!=NONE)
                player.movement();
        //Draw Map
        drawMap();

        //Finished Level
        if (player.x==table.exitX and player.y==table.exitY)
        {
            player.difficulty++;
            worldGenerate();
            table.gridSave();
            player.playerSave();
        }

    }

    table.gridSave();
    return 0;
}
