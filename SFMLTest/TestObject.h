#pragma once

#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <SFML/Graphics.hpp>
#include "WorldObject.h"

namespace SFMLTest
{
	class TestObject : public WorldObject
	{
	public:
		TestObject() : WorldObject()
		{
			rectangle = sf::RectangleShape(this->boundingBox);
			rectangle.setFillColor(sf::Color::Blue);
		}

		TestObject(const sf::Color &color, sf::Vector2f boundingBox, sf::Vector2f position, sf::Vector2f velocity, float weight) : 
			WorldObject(boundingBox, position, velocity, weight)
		{
			rectangle = sf::RectangleShape(this->boundingBox);
			rectangle.setFillColor(color);
		}

		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states)
		{
			target.draw(rectangle);
		}

	private:
		sf::RectangleShape rectangle;
	};
};
#endif