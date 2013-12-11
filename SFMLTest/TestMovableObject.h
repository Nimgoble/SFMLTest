#pragma once

#ifndef TESTMOVABLEOBJECT_H
#define TESTMOVABLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "WorldObject.h"

namespace SFMLTest
{
	class TestMovableObject : public WorldObject
	{
	public:
		TestMovableObject() : WorldObject()
		{
			type = Movable;
			defaultColor = sf::Color::White;
			rectangle = sf::RectangleShape(sf::Vector2f(this->aabb.Extents().x, aabb.Extents().y));
			rectangle.setFillColor(sf::Color::Yellow);
			rectangle.setOrigin(aabb.Extents().x / 2, aabb.Extents().y / 2);
			rectangle.setPosition(aabb.Position().x, aabb.Position().y);
		}

		~TestMovableObject()
		{
		}

		TestMovableObject(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight,
					float maxX,
					float minX) : 
		WorldObject(WorldObjectType::Movable, boundingBox, position, velocity, weight)
		{
			rectangle = sf::RectangleShape(sf::Vector2f(this->aabb.Extents().x, aabb.Extents().y));
			defaultColor = color;
			rectangle.setFillColor(color);
			sf::Vector2f origin = sf::Vector2f(boundingBox.x / 2, boundingBox.y / 2);
			rectangle.setOrigin(origin);
			aabb.Move(origin);
			rectangle.setPosition(sf::Vector2f(aabb.Position().x, aabb.Position().y));
			this->maxX = maxX;
			this->minX = minX;
		}

		virtual void OnPreTick()
		{
			//bounce back and forth
			if(aabb.Position().x > maxX || aabb.Position().x < minX)
				velocity.x *= -1;

			setPosition(aabb.Position() + velocity);

			currentFrameCollisions.clear();
		}

		virtual void ProcessCollisions()
		{
			if(currentFrameCollisions.size() > 0)
				velocity.x *= -1;//reverse direction upon contact
		}

		virtual void OnTick()
		{
			//if(currentFrameCollisions.size() <= 0)
				//setColor(sf::Color::White);
			rectangle.setPosition(sf::Vector2f(aabb.Position().x, aabb.Position().y));
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
		float maxX;
		float minX;
	};
};
#endif