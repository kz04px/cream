#include <iostream>
#include "cream/engine.hpp"

int main(int argc, char **argv)
{
    for(int i = 0; i < argc; ++i)
    {
        std::cout << std::string(argv[i]) << std::endl;
    }

    std::cout << "Welcome to Cream!" << std::endl;
    std::cout << "Version: " << cream::version << std::endl;
    std::cout << "Built on: " << cream::build << std::endl;
    std::cout << "Created by: " << cream::author << std::endl;
    std::cout << "URL: " << cream::url << std::endl;
    std::cout << "About: " << cream::about << std::endl;
    std::cout << std::endl;

    cream::Engine engine;
    engine.load_settings("settings.ini");
    engine.print();

    while(engine.run())
    {
        engine.update();
    }

    return 0;
}
