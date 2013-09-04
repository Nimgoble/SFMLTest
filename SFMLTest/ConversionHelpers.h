#pragma once
#ifndef CONVERSIONHELPERS_H
#define CONVERSIONHELPERS_H

#include "Box2D\Box2D.h"
#include <SFML\Graphics.hpp>

namespace SFMLTest
{
	static float conversionFactor = 50.0f;

	static b2Vec2 SFMLVecToB2Vec( const sf::Vector2f &vec )
	{
		return b2Vec2(vec.x / conversionFactor, vec.y / conversionFactor);
	}

	static sf::Vector2f B2VecToSFMLVec( const b2Vec2 &vec )
	{
		return sf::Vector2f(vec.x * conversionFactor, vec.y * conversionFactor);
	}
}

#endif