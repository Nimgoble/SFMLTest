#pragma once

#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

namespace SFMLTest
{
	class Line : public sf::Drawable
	{
	public:
		Line();

		Line(sf::Vector2f start, sf::Vector2f end)
		{
			this->start = start;
			this->end = end;
			vertexArray = sf::VertexArray(sf::LinesStrip, 2);
			vertexArray[0] = (sf::Vertex(sf::Vector2f(start.x, start.y)));
			vertexArray[1] = (sf::Vertex(sf::Vector2f(end.x, end.y)));
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(vertexArray, states);
		}

	private:
		sf::VertexArray vertexArray;
		sf::Vector2f start;
		sf::Vector2f end;
	};
};


#endif