#include "WorldObject.h"

using namespace SFMLTest;

WorldObject::WorldObject()
{
}

WorldObject::WorldObject(sf::Vector2<int> boundingBox, sf::Vector2f position, sf::Vector2f velocity, float weight)
{
	this->boundingBox = boundingBox;
	this->position = position;
	this->velocity = velocity;
	this->weight = weight;
}

void WorldObject::OnTick()
{
}