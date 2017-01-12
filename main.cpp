#include "worldgen.h"

#ifndef included_player
#define included_player
#include "player.h"
#endif

#include "drawmap.h"

int main()
{
    table.width=60;
    table.height=60;
    worldGenerate();
    table.gridSave();

    textureLoad();

    while(Window.isOpen())
    {
        //Able to close window
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

        //Player Move
        player.input();
        if (player.directionMove!=NONE)
            player.movement();

        //Draw Map
        drawMap();
    }

    table.gridSave();
    return 0;
}
