#include <iostream>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "game.hpp"

int main( void )
{
	// window config
    
    // elements
    
    
    Game game({SCREEN_WIDTH, SCREEN_HEIGHT}, "Snake Game");
    
    game.run();
    
	std::cout << "Exiting game...\n";
	
}
