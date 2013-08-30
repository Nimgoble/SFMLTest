#include "World.h"

using namespace SFMLTest;

World::World( sf::RenderWindow *window )
{
	size = sf::Vector2f(600.0f, 400.0f);
	tileSize = 25;
	grid = Grid(sf::Vector2f(0.0f, 0.0f), size, tileSize);
	this->window = window;
}

void World::Tick()
{
	DoCollisions();
	DrawObjects();
}

void World::DoCollisions()
{
	std::vector<WorldObject>::iterator iter = worldObjects.begin();
	std::vector<WorldObject>::iterator iterEnd = worldObjects.end();

	while(iter != iterEnd)
	{
		WorldObject &object = *(iter);
		std::vector<WorldObject>::iterator nextIter = iter;
		++nextIter;

		while(nextIter != iterEnd)
		{
			WorldObject &nextObject = *(nextIter);

		}
	}
}

void World::DrawObjects()
{
	window->clear();
	window->draw(grid);

	std::vector<WorldObject>::iterator iter = worldObjects.begin();
	std::vector<WorldObject>::iterator iterEnd = worldObjects.end();

	while(iter != iterEnd)
	{
	}

	window->display();
}