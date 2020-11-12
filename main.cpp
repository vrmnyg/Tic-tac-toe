#include <iostream>
#include <sstream>
#include "board.h"
#include "game.h"

// g++ -c -Wall -ansi main.cpp node.cpp board.cpp game.cpp
// g++ -o game main.o node.o board.o game.o
// ./game


// main program
// read board size from the command line and start game
int main(int argc, const char** argv)
{
    if (argc < 2 || argc > 2)
	{
		std::cout << "error! \n";
		return -1;
	}
    else
    {
        std::istringstream ss(argv[1]);
        int x;
        if (!(ss >> x))
        {
            std::cerr << "Invalid number " << argv[1] << '\n';
            return -1;
        }
        else
        {   
            ss >> x;
            std::cout << "You chose = " << x << "\n";
            if(x > 2)
            {
                unsigned int size = x;
                Game new_game(size);
                new_game.Execute();
            }
            else
            {
                std::cerr << "Invalid number " << argv[1] << '\n';
                std::cerr << "Size must be larger than 2!" << '\n';
                return -1;    
            }
        }
    }
}