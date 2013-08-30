#include "World.h"
#include "TestObject.h"

using namespace SFMLTest;

World::World( sf::RenderWindow *window )
{
	size = sf::Vector2f(600.0f, 400.0f);
	tileSize = 25;
	grid = Grid(sf::Vector2f(0.0f, 0.0f), size, tileSize);
	this->window = window;
	CreateTestObjects();
}



void World::Tick()
{
	DoCollisions();
	TickObjects();
}

void World::DoCollisions()
{
	std::vector<WorldObject>::iterator iter = worldObjects.begin();
	std::vector<WorldObject>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		WorldObject &object = *(iter);
		std::vector<WorldObject>::iterator nextIter = iter;
		++nextIter;

		for(; nextIter != iterEnd; nextIter++)
		{
			WorldObject &nextObject = *(nextIter);

		}
	}
}

void World::TickObjects()
{
	window->clear();
	window->draw(grid);

	std::vector<WorldObject>::iterator iter = worldObjects.begin();
	std::vector<WorldObject>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		iter->OnTick();
		window->draw(*iter);
	}

	window->display();
}

void World::CreateTestObjects()
{
	sf::Vector2f boundingBox(this->tileSize * 1.0f, this->tileSize * 1.0f);

	sf::Vector2f position((float)this->tileSize, this->tileSize * 2.0f);

	//Top row
	for(int i = 0; i < 10; i++)
	{
		position.x = this->tileSize + (this->tileSize * i);
		TestObject object(sf::Color::Blue, boundingBox, position, sf::Vector2f(), 0.0f);
		worldObjects.push_back(object);
	}

	position.x = (float)this->tileSize;
	position.y = this->tileSize * 6.0f;
	//Bottom row
	for(int i = 0; i < 10; i++)
	{
		position.x = this->tileSize + (this->tileSize * i);
		TestObject object(sf::Color::Blue, boundingBox, position, sf::Vector2f(), 0.0f);
		worldObjects.push_back(object);
	}
}