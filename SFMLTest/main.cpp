#include <SFML/Graphics.hpp>
#include "World.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");

	SFMLTest::World world(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		world.Tick();
    }

    return 0;
}