// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
using namespace sf;
using namespace std;


int main()
{
    Board Windowsize(true);
    sf::RenderWindow window(sf::VideoMode(Windowsize.getWidth(), Windowsize.getHeight()), "Minesweeper");
    
    Board board;

    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            { 
            case sf::Event::Closed: 
                window.close();
                break;
            
            default: 
                window.clear(Color(255, 255, 255, 255));

                board.refresh(window);

                window.display();
            }
           
        }
      
    }
    TextureManager::Clear();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
