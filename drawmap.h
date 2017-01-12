/// drawing a map

#ifndef included_grid
#define included_grid
#include "grid.h"
#endif

void drawMap()
{
    std::ifstream openfile("grid.txt");
    std::ifstream openfiletexture("texture.txt");

    sf::Texture tileTexture;
    sf::Sprite mapTile;


    if (openfiletexture.is_open())
    {
        std::string tileLocation;
        openfile >> tileLocation;
        tileTexture.loadFromFile(tileLocation);
        mapTile.setTexture(tileTexture);
    }

    sf::RenderWindow Window(sf::VideoMode(960, 960, 32), "RogueLike");

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

        Window.clear();

        table.gridLoad();

        for (int index_y=0; index_y<table.height; index_y++)
        {
            for (int index_x=0; index_x<table.width; index_x++)
                if (table.grid[index_x][index_y]=="wall")
                {
                    cout << table.grid[index_x][index_y] << ' ';
                    mapTile.setPosition(index_x*32, index_y*32);
                    mapTile.setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
                    Window.draw(mapTile);
                }
                else if (table.grid[index_x][index_y]=="floor")
                    {
                        cout << table.grid[index_x][index_y] << ' ';
                        mapTile.setPosition(index_x*32, index_y*32);
                        mapTile.setTextureRect(sf::IntRect(0 * 32, 1 * 32, 32, 32));
                        Window.draw(mapTile);
                    }
        }
        Window.display();
    }
}
