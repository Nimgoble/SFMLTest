#include "Player.h"
#include "ConversionHelpers.h"
using namespace SFMLTest;

Player::Player(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight, 
					b2Body *boxBody) :
			WorldObject(boundingBox, position, velocity, weight)
{
	this->boxBody = boxBody;
	boxBody->SetAwake(true);
	boxBody->SetActive(true);
	boxBody->SetGravityScale(10.0f);
	boxBody->SetTransform(SFMLVecToB2Vec(position), 0.0f);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(boundingBox.x / conversionFactor  , boundingBox.y / conversionFactor  );
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 25.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	boxFixture = boxBody->CreateFixture(&fixtureDef);
	rectangle.setFillColor(color);

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
		velocity.x = -0.5 * 1000;
	//Go right
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x = 0.5 * 1000;
	else
		velocity.x = 0.0f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y = 0.5f * 1000;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y = -0.5f * 1000;
	else
		velocity.y = 0.0f;

	//boxBody->ApplyForceToCenter(b2Vec2(velocity.x, velocity.y));
	boxBody->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), boxBody->GetWorldCenter());

	position = B2VecToSFMLVec(boxBody->GetTransform().p);
	sf::Vector2f bodyVelocity = sf::Vector2f(boxBody->GetLinearVelocity().x, boxBody->GetLinearVelocity().y);
	sf::Vector2f bodyPosition = sf::Vector2f(boxBody->GetPosition().x, boxBody->GetPosition().y);
	char buffer[64]; //String.Format, C++.  Get with the times, cunts.
	sprintf(buffer, "%.02f, %.02f - %.02f, %.02f\0", bodyVelocity.x, bodyVelocity.y, bodyPosition.x, bodyPosition.y);
	debugText.setString(buffer);
	debugText.setPosition(position.x - 20, position.y - 20);
	//Jumping should go here.
	rectangle.setPosition(position);
	rectangle.setSize(boundingBox);
}

//Do nothing is the default behavior
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//rectangle.setPosition(position);

	target.draw(rectangle, states);
	target.draw(debugText, states);
}