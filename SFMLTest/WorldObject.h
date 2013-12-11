#pragma once

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <list>
#include <SFML/Graphics.hpp>
#include "AABB.h"
#include "CollisionInformation.h"

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
		WorldObject(WorldObjectType type, sf::Vector2f boundingBox, sf::Vector2f position, sf::Vector2f velocity, float weight);

		virtual void OnPreTick();
		virtual void OnTick();

		virtual CollisionType CheckCollision(const WorldObject &other);
		virtual bool CheckCollision(const WorldObject &other, CollisionInformation &information);

		//(Most)Walls don't need collision information 
		virtual bool WantsCollisionInformation() {return (this->type == WorldObjectType::Movable);};
		//Add to our list as they are made
		virtual void OnCollision(CollisionInformation collision) {currentFrameCollisions.push_back(collision);};
		//Called after all collisions are calculated, so we can process them all at once.
		virtual void ProcessCollisions() {/*currentFrameCollisions.clear();*/};

		//Accessors and Modifiers
		const sf::Vector2f &getBoundingBox() const {return aabb.Extents();}
		void setBoundingBox(sf::Vector2f newBoundingBox) {aabb.setExtents(newBoundingBox);}

		const sf::Vector2f &getPosition() const {return aabb.Position();}
		void setPosition(sf::Vector2f newPosition) {aabb.setPosition(newPosition);}

		const AABB &getAABB() const {return aabb;}
		void setAABB( const AABB &other ) {aabb = other;}

		const sf::Vector2f &getVelocity() const {return velocity;}
		void setVelocity(sf::Vector2f newVelocity) {velocity = newVelocity;}

		void applyImpulse(sf::Vector2f impulse) {velocity += impulse;}

		const float &getWeight() const {return weight;}
		void setWeight(int newWeight) {weight = newWeight;}

		const WorldObjectType &getType() const {return type;}

		//debugging
		virtual void setColor(const sf::Color &color) {}
		virtual void setDefaultColor(const sf::Color &color) {defaultColor = color;}
		virtual void resetColor() {};
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//sf::Vector2f boundingBox;
		//sf::Vector2f position;
		sf::Vector2f velocity;
		AABB aabb;
		float weight;

		sf::Color defaultColor;

		WorldObjectType type;

		typedef std::list<CollisionInformation> CollisionList;
		CollisionList currentFrameCollisions;

		bool TestCollisionMethod(const AABB &A1, const AABB &B1);
	};
};

#endif