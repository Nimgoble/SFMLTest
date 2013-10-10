#pragma once

#ifndef AABB_H
#define AABB_H

#include<math.h>
#include <SFML/Graphics.hpp>

class AABB
{
public:
	sf::Vector3f P; //position
	sf::Vector3f E; //x,y,z extents
	AABB(){}
	AABB( const sf::Vector3f& p, const sf::Vector3f& e ):	P(p), E(e) {}

	//returns true if this is overlapping b
	const bool overlaps( const AABB& b ) const
	{
		const sf::Vector3f T = b.P - P;//vector from A to B
		bool rtn = fabs(T.x) <= ((E.x + b.E.x) / 2.0f) && fabs(T.y) <= ((E.y + b.E.y) / 2.0f) && fabs(T.z) <= (E.z + b.E.z);
		return	rtn;
	}

	//NOTE: since the vector indexing operator is not const,
	//we must cast away the const of the this pointer in the
	//following min() and max() functions
	//min x, y, or z
	const sf::Vector3f min() const
	{
		return sf::Vector3f( ((AABB*)this)->P.x - (((AABB*)this)->E.x / 2.0f),
							 ((AABB*)this)->P.y - (((AABB*)this)->E.y / 2.0f),
							 ((AABB*)this)->P.z - (((AABB*)this)->E.z / 2.0f)
							);
	}

	//max x, y, or z
	const sf::Vector3f max() const
	{
		return sf::Vector3f( ((AABB*)this)->P.x + (((AABB*)this)->E.x / 2.0f),
							 ((AABB*)this)->P.y + (((AABB*)this)->E.y / 2.0f),
							 ((AABB*)this)->P.z + (((AABB*)this)->E.z / 2.0f)
							);
	}

	/*
	const bool AABBSweep
		(
			const sf::Vector3f&	Ea,	//extents of AABB A
			const sf::Vector3f&	A0,	//its previous position
			const sf::Vector3f&	A1,	//its current position
			const sf::Vector3f&	Eb,	//extents of AABB B
			const sf::Vector3f&	B0,	//its previous position
			const sf::Vector3f&	B1,	//its current position
			float&	 u0,	//normalized time of first collision
			float&	 u1	//normalized time of second collision
		)
	{
		const AABB A( A0, Ea );//previous state of AABB A
		const AABB B( B0, Eb );//previous state of AABB B
		const sf::Vector3f va = A1 - A0;//displacement of A
		const sf::Vector3f vb = B1 - B0;//displacement of B
		//the problem is solved in A's frame of reference

		//relative velocity (in normalized time)
		sf::Vector3f v = vb - va;

		//first times of overlap along each axis
		sf::Vector3f u_0(0,0,0);

		//last times of overlap along each axis
		sf::Vector3f u_1(1,1,1);

		//check if they were overlapping on the previous frame
		if( A.overlaps(B) )
		{
			u0 = u1 = 0;
			return true;
		}

		//find the possible first and last times
		//of overlap along each axis
		for( long i=0 ; i<3 ; i++ )
		{
			if( A.max(i)<B.min(i) && v[i]<0 )
			{
				u_0[i] = (A.max(i) - B.min(i)) / v[i];
			}
			else if( B.max(i)<A.min(i) && v[i]>0 )
			{
				u_0[i] = (A.min(i) - B.max(i)) / v[i];
			}
			if( B.max(i)>A.min(i) && v[i]<0 )
			{
				u_1[i] = (A.min(i) - B.max(i)) / v[i];
			}
			else if( A.max(i)>B.min(i) && v[i]>0 )
			{
				u_1[i] = (A.max(i) - B.min(i)) / v[i];
			}
		}

		//possible first time of overlap
		u0 = std::max( u_0.x, std::max(u_0.y, u_0.z) );

		//possible last time of overlap
		u1 = std::min( u_1.x, std::min(u_1.y, u_1.z) );

		//they could have only collided if
		//the first time of overlap occurred
		//before the last time of overlap
		return u0 <= u1;
	}
	*/
};

#endif