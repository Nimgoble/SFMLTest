#pragma once

#ifndef COLLISIONINFORMATION_H
#define COLLISIONINFORMATION_H

namespace SFMLTest
{
	//Is the collision information a prediction, or are we CURRENTLY colliding?
	enum CollisionType
	{
		None,
		Prediction,
		Absolute
	};

	enum CollisionSide
	{
		Top,
		Right,
		Bottom,
		Left
	};

	class WorldObject;
	struct CollisionInformation
	{
		WorldObject *collidedWith;
		CollisionType type;
		float collisionTime;
		sf::Vector3f normal;
	};
};

#endif