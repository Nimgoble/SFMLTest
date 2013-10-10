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
		WorldObject(WorldObjectType type, sf::Vector3f boundingBox, sf::Vector3f position, sf::Vector3f velocity, float weight);

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
		const sf::Vector3f &getBoundingBox() const {return aabb.E;}
		void setBoundingBox(sf::Vector3f newBoundingBox) {aabb.E = newBoundingBox;}

		const sf::Vector3f &getPosition() const {return aabb.P;}
		void setPosition(sf::Vector3f newPosition) {aabb.P = newPosition;}

		const AABB &getAABB() const {return aabb;}
		void setAABB( const AABB &other ) {aabb = other;}

		const sf::Vector3f &getVelocity() const {return velocity;}
		void setVelocity(sf::Vector3f newVelocity) {velocity = newVelocity;}

		void applyImpulse(sf::Vector3f impulse) {velocity += impulse;}

		const float &getWeight() const {return weight;}
		void setWeight(int newWeight) {weight = newWeight;}

		const WorldObjectType &getType() const {return type;}

		//debugging
		virtual void setColor(const sf::Color &color) {}
		virtual void setDefaultColor(const sf::Color &color) {defaultColor = color;}
		virtual void resetColor() {};
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//sf::Vector3f boundingBox;
		//sf::Vector3f position;
		sf::Vector3f velocity;
		AABB aabb;
		float weight;

		sf::Color defaultColor;

		WorldObjectType type;

		typedef std::list<CollisionInformation> CollisionList;
		CollisionList currentFrameCollisions;
	};
};

#endif