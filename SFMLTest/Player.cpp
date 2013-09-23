#include "Player.h"
#include "ConversionHelpers.h"
using namespace SFMLTest;

Player::Player(const sf::Color &color, 
					sf::Vector3f boundingBox, 
					sf::Vector3f position, 
					sf::Vector3f velocity, 
					float weight) :
				WorldObject(WorldObjectType::Movable, boundingBox, position, velocity, weight)
{
	debugFont.loadFromFile("E:\\Programming\\GitHub\\SFMLTest\\Fonts\\secrcode.ttf");
	debugText.setFont(debugFont);
	debugText.setCharacterSize(12);
	debugText.setStyle(sf::Text::Bold);
	debugText.setColor(sf::Color::Magenta);
}
void Player::OnTick()
{
	
	//Go left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x = -0.5 * 1;
	//Go right
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x = 0.5 * 1;
	else
		velocity.x = 0.0f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y = 0.5f * 1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y = -0.5f * 1;
	else
		velocity.y = 0.0f;

	//position += velocity;
	/*sf::Vector3f bodyVelocity = sf::Vector3f(boxBody->GetLinearVelocity().x, boxBody->GetLinearVelocity().y);
	sf::Vector3f bodyPosition = sf::Vector3f(boxBody->GetPosition().x, boxBody->GetPosition().y);
	char buffer[64]; //String.Format, C++.  Get with the times, cunts.
	sprintf(buffer, "%.02f, %.02f - %.02f, %.02f\0", bodyVelocity.x, bodyVelocity.y, bodyPosition.x, bodyPosition.y);
	debugText.setString(buffer);
	debugText.setPosition(position.x - 20, position.y - 20);*/
	//Jumping should go here.
	rectangle.setPosition(sf::Vector2f(aabb.P.x, aabb.P.y));
	rectangle.setSize(sf::Vector2f(aabb.E.x, aabb.E.y));
}

//Do nothing is the default behavior
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//rectangle.setPosition(position);

	target.draw(rectangle, states);
	target.draw(debugText, states);
}