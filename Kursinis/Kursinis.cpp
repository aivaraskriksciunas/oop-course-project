#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "LevelLoader.h"

int main()
{
    // Load level list
    LevelLoader level_loader;
    int level_count;

    try {
        level_count = level_loader.load_level_list();
    }
    catch ( const char* err ) {
        std::cout << "Error: ";
        std::cout << err << std::endl;
        std::cout << "Game could not be launched\n";
        return 0;
    }

    // Load resources, such as images
    ResourceManager rmanager;

    try {
        rmanager.load_resources();
    }
    catch ( const std::invalid_argument& e )
    {
        std::cout << "Game could not be loaded.\n";
        std::cout << e.what() << "\n";
        return 0;
    }

    // Make resource manager available globally 
    ServiceLocator::provide( &rmanager );

    Game game;
    bool should_quit = false;

    std::cout << "Circuits\n";

    while ( !should_quit )
    {
        std::cout << "\n";
        std::cout << "Choose level:\n";

        level_loader.print_level_list();

        std::cout << "0: Quit\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if ( choice == 0 )
            should_quit = true;
        else if ( choice > level_count )
            std::cout << "Invalid choice\n\n";
        else
        {
            Level lvl = level_loader.get_level( choice - 1 );
            std::cout << '\n';
            std::cout << "--------------------- " << '\n';
            std::cout << "Tests for this level: " << '\n';
            std::cout << "--------------------- " << '\n';

            for ( int l = 0; l < lvl.test_cases.size(); l++ )
            {
                std::cout << lvl.test_cases[l][0] << " -> " << lvl.test_cases[l][1] << '\n';
            }
            game.start( lvl, 1024, 720 );
        }
    }
    
}