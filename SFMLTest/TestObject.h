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
			defaultColor = sf::Color::Red;
			rectangle = sf::RectangleShape(sf::Vector2f(this->aabb.Extents().x, aabb.Extents().y));
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setOrigin(aabb.Extents().x / 2, aabb.Extents().y / 2);
			rectangle.setPosition(aabb.Position());
		}

		~TestObject()
		{
		}

		TestObject(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight) : 
		WorldObject(WorldObjectType::Static, boundingBox, position, velocity, weight)
		{
			rectangle = sf::RectangleShape(aabb.Extents());
			defaultColor = color;
			rectangle.setFillColor(color);
			sf::Vector2f origin = sf::Vector2f(boundingBox.x / 2, boundingBox.y / 2);
			rectangle.setOrigin(origin);
			aabb.Move(origin);
			rectangle.setPosition(aabb.Position());
		}

		virtual void setColor(const sf::Color &color) { rectangle.setFillColor(color);}
		virtual void resetColor() {rectangle.setFillColor(defaultColor);}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rectangle, states);
			WorldObject::draw(target, states);
		}

	private:
		sf::RectangleShape rectangle;
	};
};
#endif