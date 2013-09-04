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
					float weight, 
					b2Body *boxBody);
		virtual void OnTick();

		void setColor(const sf::Color &color) {rectangle.setFillColor(color);}
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::RectangleShape rectangle;
		b2Fixture *boxFixture;

		sf::Font debugFont;
		sf::Text debugText;
	};
};

#endif