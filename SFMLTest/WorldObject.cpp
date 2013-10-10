#include "WorldObject.h"
#include "ConversionHelpers.h"

using namespace SFMLTest;

WorldObject::WorldObject()
{
}

WorldObject::WorldObject(WorldObjectType type, sf::Vector3f boundingBox, sf::Vector3f position, sf::Vector3f velocity, float weight)
{
	this->type = type;
	this->aabb.E = boundingBox;
	this->aabb.P = position;
	this->velocity = velocity;
	this->weight = weight;
}

//Nothing.
void WorldObject::OnPreTick()
{
	//currentFrameCollisions.clear();
}

//Nothing.
void WorldObject::OnTick()
{
}

CollisionType WorldObject::CheckCollision(const WorldObject &other)
{
	//Static stuff ignores each other.
	if(this->type == WorldObjectType::Static && other.getType() == WorldObjectType::Static)
		return CollisionType::None;

	const AABB A0( aabb.P, aabb.E );//current state of AABB A
	const AABB &B0 = other.getAABB();//current state of AABB other
	const AABB A1( A0.P + velocity, A0.E ); //Projected state of us
	const AABB B1( B0.P + (other.getVelocity()), B0.E); //Projected state of other
	const sf::Vector3f va = velocity;//displacement of A
	const sf::Vector3f vb = other.getVelocity();//displacement of B

	float timeMin = 0.0f, timeMax = 0.0f;
	//the problem is solved in A's frame of reference

	//relative velocity (in normalized time)
	sf::Vector3f v = vb - va;

	//first times of overlap along each axis
	sf::Vector3f u_0(0,0,0);

	//last times of overlap along each axis
	sf::Vector3f u_1(1,1,1);

	//check if they were overlapping on the current frame
	if( A0.overlaps(B0) )
	{
		timeMin = timeMax = 0;
		return CollisionType::Absolute;
	}

	//Prediction:
	if(A1.overlaps(B1))
		return CollisionType::Prediction;

	sf::Vector3f intersectionPoint;
	if(!SFMLTest::DoLinesIntersect(A0.P, A1.P, B0.P, B1.P, intersectionPoint))
		return CollisionType::None;

	//Find the time at which we would come to the intersection point

	//Difference between intersection point and where we started this frame
	sf::Vector3f intersectionTime = intersectionPoint - A0.P;
	//What percentage of our velocity is the distance we are from the intersection point?
	intersectionTime.x /= va.x;
	intersectionTime.y /= va.y;

	//TODO: Bullet through paper problem using the above intersection time

	return CollisionType::None;

	//find the possible first and last times
	//of overlap along each axis

	/*sf::Vector3f AMin = A0.min(), AMax = A0.max();
	sf::Vector3f BMin = B0.min(), BMax = B0.max();

	//X
	if( AMax.x < BMin.x && v.x < 0)
		u_0.x = (AMax.x - BMin.x) / v.x;
	else if(BMax.x < AMin.x && v.x > 0)
		u_0.x = (AMin.x - BMax.x) / v.x;

	if(BMax.x > AMin.x && v.x < 0)
		u_1.x = (AMin.x - BMax.x) / v.x;
	else if( AMax.x > BMin.x && v.x > 0)
		u_1.x = (AMax.x - BMin.x) / v.x;

	//Y
	if( AMax.y < BMin.y && v.y < 0)
		u_0.y = (AMax.y - BMin.y) / v.y;
	else if(BMax.y < AMin.y && v.y > 0)
		u_0.y = (AMin.y - BMax.y) / v.y;

	if(BMax.y > AMin.y && v.y < 0)
		u_1.y = (AMin.y - BMax.y) / v.y;
	else if( AMax.y > BMin.y && v.y > 0)
		u_1.y = (AMax.y - BMin.y) / v.y;

	//Z
	if( AMax.z < BMin.z && v.z < 0)
		u_0.z = (AMax.z - BMin.z) / v.z;
	else if(BMax.z < AMin.z && v.z > 0)
		u_0.z = (AMin.z - BMax.z) / v.z;

	if(BMax.z > AMin.z && v.z < 0)
		u_1.z = (AMin.z - BMax.z) / v.z;
	else if( AMax.z > BMin.z && v.z > 0)
		u_1.z = (AMax.z - BMin.z) / v.z;

	//possible first time of overlap
	timeMin = std::max( u_0.x, std::max(u_0.y, u_0.z) );

	//possible last time of overlap
	timeMax = std::min( u_1.x, std::min(u_1.y, u_1.z) );

	//they could have only collided if
	//the first time of overlap occurred
	//before the last time of overlap
	bool rtn = timeMin > timeMax;
	return rtn;*/
}

bool WorldObject::CheckCollision(const WorldObject &other, CollisionInformation &information)
{
	//TODO: all of this.
	return false;
}

//Do nothing is the default behavior
void WorldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//OnDraw(&target, states);
}
