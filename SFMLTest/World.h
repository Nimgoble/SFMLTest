///BLAH BLAH BLAH
#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "WorldObject.h"
#include "DebugDrawer.h"
#include "Box2D\Box2D.h"

namespace SFMLTest
{
	class World
	{
	public:
		World( sf::RenderWindow *window );
		//Called each tick.  Does all the internal stuff
		void Tick();
		void Cleanup();
	private:
		//private methods
		void TickObjects();
		void DoCollisions();

		void CreateTestObjects();

		sf::Vector2f TileToVector(int column, int row);
		sf::Vector2f TileToBoundingBox(int widthInTiles, int heightInTiles);

		inline int Rows() {return (int)(size.y / tileSize);}
		inline int Columns() {return (int)(size.x / tileSize);}

		//private variables
		sf::Vector2f size;
		int tileSize;

		sf::RenderWindow *window;
		sf::Clock clock;

		b2Vec2 gravity;
		b2World *world;

		Grid grid;
		DebugDrawer debugDrawer;

		std::vector<WorldObject *> worldObjects;
		std::vector<b2Body *> b2Bodies;
	};
};

#endif