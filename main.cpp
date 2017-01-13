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
    ifstream file("grid.txt");

    if (file.good())
    {
        file.close();
        table.gridLoad();
        player.playerLoad();
        enemyLoad();
    }
    else
    {
        worldGenerate();
        table.gridSave();
        player.playerSave();
        enemySave();
    }

    textureLoad();

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
                table.gridSave();
                player.playerSave();
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
                    table.gridSave();
                    player.playerSave();
                    enemySave();
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
            enemySave();
        }

        //DIE
        if (player.health<=0)
        {
            remove("grid.txt");
            remove("player.txt");
            remove("enemy.txt");
            Window.close();
        }

    }


    return 0;
}
