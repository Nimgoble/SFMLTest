#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "WorldObject.h"

namespace SFMLTest
{
	class Player : public WorldObject
	{
	public:
		Player(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight);

		virtual void OnPreTick();
		virtual void OnTick();
		virtual void ProcessCollisions();

		virtual void setColor(const sf::Color &color) {rectangle.setFillColor(color);}
		virtual void resetColor() {rectangle.setFillColor(defaultColor);}
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::RectangleShape rectangle;

		//Debugging
		sf::RectangleShape minShape, maxShape;

		sf::Font debugFont;
		sf::Text debugText;
	};
};

#endif