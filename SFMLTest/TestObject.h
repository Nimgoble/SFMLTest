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
			rectangle = sf::RectangleShape(this->boundingBox);
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(position);
		}

		~TestObject()
		{
		}

		TestObject(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight, 
					b2Body *boxBody) : 
			WorldObject(boundingBox, position, velocity, weight)
		{
			this->boxBody = boxBody;
			boxBody->SetTransform(b2Vec2(position.x / conversionFactor  , position.y / conversionFactor  ), 0.0f);
			b2PolygonShape shapeBox;
			shapeBox.SetAsBox(boundingBox.x / conversionFactor  , boundingBox.y / conversionFactor  );
			boxFixture = boxBody->CreateFixture(&shapeBox, 0.0f);

			rectangle = sf::RectangleShape(this->boundingBox);
			rectangle.setFillColor(color);
			rectangle.setPosition(position);
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rectangle, states);
		}

	private:
		sf::RectangleShape rectangle;
		b2Fixture *boxFixture;
	};
};
#endif