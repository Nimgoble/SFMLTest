#pragma once 

#ifndef GRID_H
#define GRID_H

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SFMLTest
{
	class Grid : public sf::Drawable
	{
	public:
		Grid();

		Grid(sf::Vector2f position, sf::Vector2f size, int stepSize);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//Accessor
		sf::Vector2f Position() {return position;}

	private:
		//Horizontal rectangles are the rectangles that stretch horizontally, but run vertically
		std::vector<sf::RectangleShape> horizontalRectangles;
		//Vertical rectangles are the rectangles that stretch vertically, but run horizontally
		std::vector<sf::RectangleShape> verticalRectangles;

		sf::Vector2f position;
	};
};

#endif