#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "definitions.hpp"
#include "game.hpp"
#include "level.hpp"

int main( void )
{
	// window config
    
    // elements
    
    Game game({SCREEN_WIDTH, SCREEN_HEIGHT}, "Snake Game");
    
    game.run();
    
	std::cout << "Exiting game...\n";
	
}
