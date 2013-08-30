///BLAH BLAH BLAH
#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "WorldObject.h"

namespace SFMLTest
{
	class World
	{
	public:
		World( sf::RenderWindow *window );
		//Called each tick.  Does all the internal stuff
		void Tick();
	private:
		//private methods
		void TickObjects();
		void DoCollisions();

		void CreateTestObjects();

		//private variables
		sf::Vector2f size;
		int tileSize;

		sf::RenderWindow *window;

		Grid grid;

		std::vector<WorldObject> worldObjects;
	};
};

#endif