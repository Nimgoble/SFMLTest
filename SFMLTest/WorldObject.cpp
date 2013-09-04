#include "WorldObject.h"

using namespace SFMLTest;

WorldObject::WorldObject()
{
}

WorldObject::WorldObject(sf::Vector2f boundingBox, sf::Vector2f position, sf::Vector2f velocity, float weight)
{
	this->boundingBox = boundingBox;
	this->position = position;
	this->velocity = velocity;
	this->weight = weight;
}

//Nothing.
void WorldObject::OnTick()
{
}

bool WorldObject::CheckCollision(const WorldObject &other)
{
	return false;
}

//Do nothing is the default behavior
void WorldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//OnDraw(&target, states);
}