#pragma once

#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include "ConversionHelpers.h"

namespace SFMLTest
{
	class TestObject : public WorldObject
	{
	public:
		TestObject() : WorldObject()
		{
			defaultColor = sf::Color::Red;
			rectangle = sf::RectangleShape(sf::Vector2f(this->aabb.E.x, aabb.E.y));
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setOrigin(aabb.E.x / 2, aabb.E.y / 2);
			rectangle.setPosition(aabb.P.x, aabb.P.y);
		}

		~TestObject()
		{
		}

		TestObject(const sf::Color &color, 
					sf::Vector3f boundingBox, 
					sf::Vector3f position, 
					sf::Vector3f velocity, 
					float weight) : 
		WorldObject(WorldObjectType::Static, boundingBox, position, velocity, weight)
		{
			rectangle = sf::RectangleShape(sf::Vector2f(this->aabb.E.x, aabb.E.y));
			defaultColor = color;
			rectangle.setFillColor(color);
			sf::Vector2f origin = sf::Vector2f(boundingBox.x / 2, boundingBox.y / 2);
			rectangle.setOrigin(origin);
			aabb.P += sf::Vector3f(origin.x, origin.y, 0.0f);
			rectangle.setPosition(sf::Vector2f(aabb.P.x, aabb.P.y));
		}

		virtual void setColor(const sf::Color &color) { rectangle.setFillColor(color);}
		virtual void resetColor() {rectangle.setFillColor(defaultColor);}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rectangle, states);
		}

	private:
		sf::RectangleShape rectangle;
	};
};
#endif