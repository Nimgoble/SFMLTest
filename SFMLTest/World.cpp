#include "World.h"
#include "TestObject.h"
#include "Player.h"

using namespace SFMLTest;

World::World( sf::RenderWindow *window )
{
	this->window = window;
	debugDrawer.setRenderTarget(window);
	debugDrawer.SetFlags( b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit );

	size = sf::Vector2f(window->getSize().x, window->getSize().y);
	tileSize = 25;
	grid = Grid(sf::Vector2f(0.0f, 0.0f), size, tileSize);

	gravity = b2Vec2(0.0f, 10.0f);
	world = new b2World(gravity);
	world->SetDebugDraw(&debugDrawer);
	
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

	for(int i = 0; i < b2Bodies.size(); i++)
	{
		world->DestroyBody(b2Bodies[i]);
	}

	delete world;
	world = NULL;
}

void World::DoCollisions()
{
	std::vector<WorldObject *>::iterator iter = worldObjects.begin();
	std::vector<WorldObject *>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		WorldObject *object = *(iter);
		std::vector<WorldObject *>::iterator nextIter = iter;
		++nextIter;

		sf::Vector2f currentPosition = object->getPosition();
		sf::Vector2f currentVelocity = object->getVelocity();

		//Collisiong detection against all of the other entities goes here:
		for(; nextIter != iterEnd; nextIter++)
		{
			WorldObject *nextObject = *(nextIter);

		}

		//Apply velocity if we can
		object->setPosition(currentPosition + currentVelocity);
	}
}

void World::TickObjects()
{
	window->clear();
	world->DrawDebugData();
	//Draw each WorldObject
	std::vector<WorldObject *>::iterator iter = worldObjects.begin();
	std::vector<WorldObject *>::iterator iterEnd = worldObjects.end();

	for(; iter != iterEnd; iter++)
	{
		(*iter)->OnTick();
		window->draw(**iter);
	}

	world->Step(1.0f/60.0f, 20, 20);
	//Draw the test grid
	window->draw(grid);
	window->display();
}

void World::CreateTestObjects()
{
	b2BodyDef bodyDef;
	//bodyDef.allowSleep = true;
	bodyDef.awake = true;
	bodyDef.active = true;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_staticBody;

	sf::Vector2f boundingBox(this->tileSize * 1.0f, this->tileSize * 1.0f);

	//sf::Vector2f position((float)this->tileSize, this->tileSize * 2.0f);

	int rows = Rows() - 1, columns = Columns() - 1;
	for(int i = 0; i <= columns; i++)
	{
		//top row
		b2Body *body = world->CreateBody(&bodyDef);
		TestObject *object1 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(0, i), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object1);
		b2Bodies.push_back(body);
		//bottom row
		body = world->CreateBody(&bodyDef);
		TestObject *object2 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(rows, i), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object2);
		b2Bodies.push_back(body);
	}

	for(int i = 1; i <= (rows - 1); i++)
	{
		//left side
		b2Body *body = world->CreateBody(&bodyDef);
		TestObject *object1 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(i, 0), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object1);
		b2Bodies.push_back(body);
		//right side
		body = world->CreateBody(&bodyDef);
		TestObject *object2 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(i, columns), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object2);
		b2Bodies.push_back(body);
	}

	int thirdOfRows = rows / 3;

	for(int i = 1; i <= 10; i++)
	{
		//platform one
		b2Body *body = world->CreateBody(&bodyDef);
		TestObject *object1 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(thirdOfRows, i), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object1);
		b2Bodies.push_back(body);
		//platform two
		body = world->CreateBody(&bodyDef);
		TestObject *object2 = new TestObject(sf::Color::Blue, boundingBox, TileToVector(thirdOfRows * 2, columns - i), sf::Vector2f(), 0.0f, body);
		worldObjects.push_back(object2);
		b2Bodies.push_back(body);
	}

	bodyDef.type = b2_dynamicBody;
	bodyDef.allowSleep = false;
	bodyDef.gravityScale = 10.0f;
	b2Body *body = world->CreateBody(&bodyDef);
	Player *player = new Player(sf::Color::Cyan, TileToBoundingBox(1, 2), TileToVector(3, 1), sf::Vector2f(), 1.0f, body);
	worldObjects.push_back(player);
	b2Bodies.push_back(body);
}

sf::Vector2f World::TileToVector(int row, int column)
{
	return sf::Vector2f((float)(tileSize * column), (float)(tileSize * row));
}

sf::Vector2f World::TileToBoundingBox(int widthInTiles, int heightInTiles)
{
	return TileToVector(heightInTiles, widthInTiles);
}