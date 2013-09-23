#pragma once

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SFML/Graphics.hpp>
#include "AABB.h"

namespace SFMLTest
{
	enum WorldObjectType
	{
		Static = 0,
		Movable = 1
	};

	class WorldObject : public sf::Drawable
	{
	public:
		WorldObject();
		WorldObject(WorldObjectType type, sf::Vector3f boundingBox, sf::Vector3f position, sf::Vector3f velocity, float weight);

		virtual void OnTick();

		virtual bool CheckCollision(const WorldObject &other);

		//Accessors and Modifiers
		const sf::Vector3f &getBoundingBox() const {return aabb.E;}
		void setBoundingBox(sf::Vector3f newBoundingBox) {aabb.E = newBoundingBox;}

		const sf::Vector3f &getPosition() const {return aabb.P;}
		void setPosition(sf::Vector3f newPosition) {aabb.P = newPosition;}

		const AABB &getAABB() const {return aabb;}
		void setAABB( const AABB &other ) {aabb = other;}

		const sf::Vector3f &getVelocity() const {return velocity;}
		void setVelocity(sf::Vector3f newVelocity) {velocity = newVelocity;}

		const float &getWeight() const {return weight;}
		void setWeight(int newWeight) {weight = newWeight;}

		const WorldObjectType &getType() const {return type;}

		//debugging
		virtual void setColor(const sf::Color &color) {}
		int currentCollisionCount;
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//sf::Vector3f boundingBox;
		//sf::Vector3f position;
		sf::Vector3f velocity;
		AABB aabb;
		float weight;

		WorldObjectType type;
	};
};

#endif