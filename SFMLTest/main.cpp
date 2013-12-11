#include <SFML/Graphics.hpp>
#include "World.h"
#include "LineSegmentTests.h"

int main()
{
	//SFMLTest::LineSegmentTests::RunTests();
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");

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

	world.Cleanup();

    return 0;
}