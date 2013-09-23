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
					sf::Vector3f boundingBox, 
					sf::Vector3f position, 
					sf::Vector3f velocity, 
					float weight);
		virtual void OnTick();

		virtual void setColor(const sf::Color &color) {rectangle.setFillColor(color);}
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::RectangleShape rectangle;

		sf::Font debugFont;
		sf::Text debugText;
	};
};

#endif