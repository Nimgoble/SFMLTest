#include "Grid.h"

using namespace SFMLTest;

Grid::Grid()
{
}

Grid::Grid(sf::Vector2f position, sf::Vector2f size, int stepSize)
{
	this->position = position;

	//Go from left to right, creating the vertical rectangles
	for(int i = 0; i < (position.x + size.x); i += stepSize)
	{
		sf::RectangleShape rect(sf::Vector2f(1.0f, size.y));				
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(sf::Vector2f(i, position.y));
		verticalRectangles.push_back(rect);
	}

	//Go from top to bottom, creating the horizontal rectangles
	for(int i = 0; i < (position.y + size.y); i += stepSize)
	{
		sf::RectangleShape rect(sf::Vector2f(size.x, 1.0f));
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(sf::Vector2f(position.x, i));
		horizontalRectangles.push_back(rect);
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(int i = 0; i < horizontalRectangles.size(); i++)
		target.draw(horizontalRectangles[i], states);

	for(int i = 0; i < verticalRectangles.size(); i++)
		target.draw(verticalRectangles[i], states);
}