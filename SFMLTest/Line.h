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

		Line(sf::Vector3f start, sf::Vector3f end)
		{
			this->start = start;
			this->end = end;
			vertexArray = sf::VertexArray(sf::Lines, 2);
			vertexArray.append(sf::Vertex(sf::Vector2f(start.x, start.y)));
			vertexArray.append(sf::Vertex(sf::Vector2f(end.x, end.y)));
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(vertexArray, states);
		}

	private:
		sf::VertexArray vertexArray;
		sf::Vector3f start;
		sf::Vector3f end;
	};
};


#endif