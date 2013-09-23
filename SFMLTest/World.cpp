#include "World.h"
#include "TestObject.h"
#include "Player.h"
#include "Line.h"

using namespace SFMLTest;

World::World( sf::RenderWindow *window )
{
	this->window = window;

	size = sf::Vector2f(window->getSize().x, window->getSize().y);
	tileSize = 32;
	grid = Grid(sf::Vector2f(0.0f, 0.0f), size, tileSize);
	
	CreateTestObjects();
}

void World::Tick()
{
	DoCollisions();
	TickObjects();
}

void World::Cleanup()
{
	for(int i = 0; i < worldObjects.size(); i++)
	{
		WorldObject *object = worldObjects[i];
		delete object;
		object = NULL;
	}
}

void World::DoCollisions()
{
	std::vector<WorldObject *>::iterator iter = worldObjects.begin();
	std::vector<WorldObject *>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		object->currentCollisionCount = 0;
	}

	iter = worldObjects.begin();
	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		std::vector<WorldObject *>::iterator nextIter = iter;
		++nextIter;

		sf::Vector3f currentPosition = object->getPosition();
		sf::Vector3f currentVelocity = object->getVelocity();

		bool collision = false;
		//Collisiong detection against all of the other entities goes here:
		for(; nextIter != iterEnd; nextIter++)
		{
			WorldObject *nextObject = *(nextIter);
			if(object->CheckCollision(*nextObject))
			{
				object->currentCollisionCount++;
				nextObject->currentCollisionCount++;
				collision = true;
				window->draw(SFMLTest::Line(object->getPosition(), nextObject->getPosition()));
			}
		}

		//Apply velocity if we can
		if(collision == false)
			object->setPosition(currentPosition + currentVelocity);
	}

	iter = worldObjects.begin();
	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		sf::Color color = (object->currentCollisionCount != 0) ? sf::Color::Magenta : sf::Color::Red;
		object->setColor(color);
	}
}

void World::TickObjects()
{
	window->clear();
	//Draw each WorldObject
	std::vector<WorldObject *>::iterator iter = worldObjects.begin();
	std::vector<WorldObject *>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		(*iter)->OnTick();
		window->draw(**iter);
	}
	
	//Draw the test grid
	window->draw(grid);
	window->display();
}

void World::CreateTestObjects()
{
	sf::Vector2f horizontalBB2D = TileToBoundingBox(36, 1);
	sf::Vector2f verticalBB2D = TileToBoundingBox(1, 23);

	sf::Vector3f horizontalBB = sf::Vector3f(horizontalBB2D.x, horizontalBB2D.y, 0.0f);
	sf::Vector3f verticalBB = sf::Vector3f(verticalBB2D.x, verticalBB2D.y, 0.0f);

	sf::Vector3f blankVector = sf::Vector3f(0, 0, 0);
	//Top bar
	TestObject *topBar = new TestObject(sf::Color::Red, horizontalBB, blankVector, blankVector, 0.0f); 
	
	//Bottom bar
	sf::Vector2f bottomPosition = TileToVector(23, 0);
	TestObject *bottomBar = new TestObject(sf::Color::Red, horizontalBB, sf::Vector3f(bottomPosition.x, bottomPosition.y, 0.0f), blankVector, 0.0f);

	//Top bar
	TestObject *leftBar= new TestObject(sf::Color::Red, verticalBB, blankVector, blankVector, 0.0f); 
	
	//Bottom bar
	sf::Vector2f rightPosition = TileToVector(0, 36);
	TestObject *rightBar = new TestObject(sf::Color::Red, verticalBB, sf::Vector3f(rightPosition.x, rightPosition.y, 0.0f), blankVector, 0.0f);


	worldObjects.push_back(topBar);
	worldObjects.push_back(bottomBar);
	worldObjects.push_back(leftBar);
	worldObjects.push_back(rightBar);

	sf::Vector2f playerBB = TileToBoundingBox(1, 2);
	sf::Vector2f playerPosition = TileToVector(1, 1);
	Player *player = new Player(
									sf::Color::Blue, 
									sf::Vector3f(playerBB.x, playerBB.y, 0.0f), 
									sf::Vector3f(playerPosition.x, playerPosition.y, 0.0f), 
									blankVector,
									1.0f
								);

	worldObjects.push_back(player);
}

sf::Vector2f World::TileToVector(int row, int column)
{
	return sf::Vector2f((float)(tileSize * column), (float)(tileSize * row));
}

sf::Vector2f World::TileToBoundingBox(int widthInTiles, int heightInTiles)
{
	return TileToVector(heightInTiles, widthInTiles);
}