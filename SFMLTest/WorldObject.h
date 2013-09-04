#pragma once

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"

namespace SFMLTest
{
	class WorldObject : public sf::Drawable
	{
	public:
		WorldObject();
		WorldObject(sf::Vector2f boundingBox, sf::Vector2f position, sf::Vector2f velocity, float weight);
		WorldObject(b2Body *boxBody) {this->boxBody = boxBody;};

		virtual void OnTick();

		virtual bool CheckCollision(const WorldObject &other);

		//Accessors and Modifiers
		sf::Vector2f getBoundingBox(){return boundingBox;}
		void setBoundingBox(sf::Vector2f newBoundingBox) {boundingBox = newBoundingBox;}

		sf::Vector2f getPosition() {return position;}
		void setPosition(sf::Vector2f newPosition) {position = newPosition;}

		sf::Vector2f getVelocity() {return velocity;}
		void setVelocity(sf::Vector2f newVelocity) {velocity = newVelocity;}

		float getWeight() {return weight;}
		void setWeight(int newWeight) {weight = newWeight;}

	protected:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Vector2f boundingBox;
		sf::Vector2f position;
		sf::Vector2f velocity;
		b2Body *boxBody;
		float weight;
	};
};

#endif