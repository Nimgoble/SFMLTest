#include "Player.h"
using namespace SFMLTest;

Player::Player(const sf::Color &color, 
					sf::Vector2f boundingBox, 
					sf::Vector2f position, 
					sf::Vector2f velocity, 
					float weight) :
				WorldObject(WorldObjectType::Movable, boundingBox, position, velocity, weight)
{
	debugFont.loadFromFile("E:\\Programming\\GitHub\\SFMLTest\\Fonts\\secrcode.ttf");
	debugText.setFont(debugFont);
	debugText.setCharacterSize(12);
	debugText.setStyle(sf::Text::Bold);
	debugText.setColor(sf::Color::Magenta);

	defaultColor = color;
	rectangle = sf::RectangleShape(sf::Vector2f(boundingBox.x, boundingBox.y));
	rectangle.setOrigin(aabb.Extents().x / 2, aabb.Extents().y / 2);
	rectangle.setFillColor(color);

	sf::Vector2f min = aabb.min(), max = aabb.max();
	sf::Vector2f shapeSize = sf::Vector2f(1.0f, 1.0f);
	minShape = sf::RectangleShape(shapeSize);
	minShape.setFillColor(sf::Color::Yellow);

	maxShape = sf::RectangleShape(shapeSize);
	maxShape.setFillColor(sf::Color::Yellow);
}
void Player::OnPreTick()
{
	//Go left
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x = -0.5 * 0.1;
	//Go right
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x = 0.5 * 0.1;
	else
		velocity.x = 0.0f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y = 0.5f * 0.1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y = -0.5f * 0.1;
	else
		velocity.y = 0.0f;
	
	//velocity.x = -0.5 * 0.1;
	//position += velocity;
	/*sf::Vector2f bodyVelocity = sf::Vector2f(boxBody->GetLinearVelocity().x, boxBody->GetLinearVelocity().y);
	sf::Vector2f bodyPosition = sf::Vector2f(boxBody->GetPosition().x, boxBody->GetPosition().y);
	char buffer[64]; //String.Format, C++.  Get with the times, cunts.
	sprintf(buffer, "%.02f, %.02f - %.02f, %.02f\0", bodyVelocity.x, bodyVelocity.y, bodyPosition.x, bodyPosition.y);
	debugText.setString(buffer);
	debugText.setPosition(position.x - 20, position.y - 20);*/
	//Jumping should go here.
	setPosition(aabb.Position() + velocity);
	//rectangle.setSize(sf::Vector2f(aabb.Extents().x, aabb.Extents().y));

	CollisionList::iterator iter = currentFrameCollisions.begin();
	CollisionList::iterator iterEnd = currentFrameCollisions.end();

	for(; iter != iterEnd; iter++)
	{
		const CollisionInformation &info = *(iter);
		info.collidedWith->resetColor();
	}

	currentFrameCollisions.clear();
}

void Player::OnTick()
{
	rectangle.setPosition(aabb.Position());
	sf::Vector2f min = aabb.min(), max = aabb.max();
	minShape.setPosition(sf::Vector2f(min.x, min.y));
	maxShape.setPosition(sf::Vector2f(max.x, max.y));
}

void Player::ProcessCollisions()
{
	//sf::Vector2f min = this->aabb.min();
	//sf::Vector2f max = this->aabb.max();
	if(currentFrameCollisions.size() <= 0)
	{
		setColor(sf::Color::Blue);
		return;
	}

	setColor(sf::Color::Magenta);

	CollisionList::iterator iter = currentFrameCollisions.begin();
	CollisionList::iterator iterEnd = currentFrameCollisions.end();

	for(; iter != iterEnd; iter++)
	{
		const CollisionInformation &info = *(iter);
		info.collidedWith->setColor(sf::Color::Magenta);
	}

	//Go back
	setPosition(aabb.Position() - velocity);
	
	//base class
	WorldObject::ProcessCollisions();
}

//Do nothing is the default behavior
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//rectangle.setPosition(position);

	target.draw(rectangle, states);
	target.draw(debugText, states);
	target.draw(minShape, states);
	target.draw(maxShape, states);
	WorldObject::draw(target, states);
}