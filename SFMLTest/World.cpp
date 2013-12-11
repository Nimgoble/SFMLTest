#include "World.h"
#include "TestObject.h"
#include "Player.h"
#include "Line.h"
#include "TestMovableObject.h"

using namespace SFMLTest;

World::World( sf::RenderWindow *window )
{
	this->window = window;

	size = sf::Vector2f(window->getSize().x, window->getSize().y);
	tileSize = 32;
	grid = Grid(sf::Vector2f(0.0f, 0.0f), size, tileSize);
	gravity = sf::Vector2f(0.0f, 0.5f);

	CreateTestObjects();
}

void World::Tick()
{
	PreTickObjects();
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
		if(object->getWeight() > 0 && object->getType() != Static)
		{
			object->applyImpulse(gravity * object->getWeight());
			object->setPosition(object->getPosition() + gravity);
		}
	}

	iter = worldObjects.begin();
	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		std::vector<WorldObject *>::iterator nextIter = iter;
		++nextIter;

		sf::Vector2f currentPosition = object->getPosition();
		sf::Vector2f currentVelocity = object->getVelocity();

		bool collision = false;
		//Collisiong detection against all of the other entities goes here:
		for(; nextIter != iterEnd; nextIter++)
		{
			WorldObject *nextObject = *(nextIter);
			CollisionType type = object->CheckCollision(*nextObject);
			if(type != CollisionType::None)
			{
				if(object->WantsCollisionInformation())
				{
					CollisionInformation info;
					info.collidedWith = nextObject;
					info.type = type;
					object->OnCollision(info);
				}

				if(nextObject->WantsCollisionInformation())
				{
					CollisionInformation info;
					info.collidedWith = object;
					info.type = type;
					nextObject->OnCollision(info);
				}

				window->draw(SFMLTest::Line(object->getPosition(), nextObject->getPosition()));
			}
		}
	}

	iter = worldObjects.begin();
	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		object->ProcessCollisions();
		/*if(object->currentCollisionCount == 0)
		{
			object->setPosition(object->getPosition() + object->getVelocity());
			object->resetColor();
		}
		else
		{
			object->setColor(sf::Color::Magenta);
			object->setVelocity(sf::Vector2f(0.0f, 0.0f, 0.0f));
			//object->setPosition(object->getPosition() + object->getVelocity());
		}*/
	}
}

void World::PreTickObjects()
{
	//Draw each WorldObject
	std::vector<WorldObject *>::iterator iter = worldObjects.begin();
	std::vector<WorldObject *>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		(*iter)->OnPreTick();
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
	/*sf::Vector2f horizontalBB2D = TileToBoundingBox(36, 1);
	sf::Vector2f verticalBB2D = TileToBoundingBox(1, 23);*/

	sf::Vector2f horizontalBB = TileToBoundingBox(36, 1);
	sf::Vector2f verticalBB = TileToBoundingBox(1, 23);

	/*sf::Vector2f horizontalBB = sf::Vector2f(horizontalBB2D.x, horizontalBB2D.y, 0.0f);
	sf::Vector2f verticalBB = sf::Vector2f(verticalBB2D.x, verticalBB2D.y, 0.0f);*/

	sf::Vector2f blankVector = sf::Vector2f(0, 0);
	//Top bar
	TestObject *topBar = new TestObject(sf::Color::Red, horizontalBB, blankVector, blankVector, 0.0f); 
	
	//Bottom bar
	sf::Vector2f bottomPosition = TileToVector(23, 0);
	TestObject *bottomBar = new TestObject(sf::Color::Red, horizontalBB, sf::Vector2f(bottomPosition.x, bottomPosition.y), blankVector, 0.0f);

	//Left bar
	TestObject *leftBar= new TestObject(sf::Color::Red, verticalBB, blankVector, blankVector, 0.0f); 
	
	//Right bar
	sf::Vector2f rightPosition = TileToVector(0, 35);
	TestObject *rightBar = new TestObject(sf::Color::Red, verticalBB, sf::Vector2f(rightPosition.x, rightPosition.y), blankVector, 0.0f);

	worldObjects.push_back(topBar);
	worldObjects.push_back(bottomBar);
	worldObjects.push_back(leftBar);
	worldObjects.push_back(rightBar);

	//Bouncing object
	TestMovableObject *movableObject = new TestMovableObject(sf::Color::White, TileToBoundingBox(2, 2), TileToVector(5, 18), sf::Vector2f(0.5f, 0.0f), 0.0f, 800.0f, 75.0f);
	worldObjects.push_back(movableObject);

	TestMovableObject *movableObject2 = new TestMovableObject(sf::Color::Yellow, sf::Vector2f(10.0f, 10.0f), TileToVector(12, 18), sf::Vector2f(5.0f, 0.0f), 0.0f, 800.0f, 75.0f);
	worldObjects.push_back(movableObject2);

	Player *player = new Player(
									sf::Color::Blue, 
									TileToBoundingBox(1, 2), 
									TileToVector(5, 5), 
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