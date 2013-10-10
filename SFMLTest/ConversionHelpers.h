#pragma once
#ifndef CONVERSIONHELPERS_H
#define CONVERSIONHELPERS_H

#include <SFML\Graphics.hpp>

#define SAME_SIGNS( a, b )	(((long) ((unsigned long) a ^ (unsigned long) b)) >= 0 )


/*
1u = 
*/
namespace SFMLTest
{
	/*static float conversionFactor = 64.0f;

	static b2Vec2 SFMLVecToB2Vec( const sf::Vector3f &vec )
	{
		return b2Vec2(vec.x / conversionFactor, vec.y / conversionFactor);
	}

	static sf::Vector3f B2VecToSFMLVec( const b2Vec2 &vec )
	{
		return sf::Vector3f(vec.x * conversionFactor, vec.y * conversionFactor);
	}*/

	static bool DoLinesIntersect(const sf::Vector3f &start1, 
								 const sf::Vector3f &end1, 
								 const sf::Vector3f &start2, 
								 const sf::Vector3f &end2, 
								 sf::Vector3f &intersectionPoint)
	{
		long a1, a2, b1, b2, c1, c2; /* Coefficients of line eqns. */
		long r1, r2, r3, r4;         /* 'Sign' values */
		long denom, offset, num;     /* Intermediate values */

		/* Compute a1, b1, c1, where line joining points 1 and 2
		 * is "a1 x  +  b1 y  +  c1  =  0".
		 */

		a1 = end1.y - start1.y;
		b1 = start1.x - end1.x;
		c1 = end1.x * start1.y - start1.x * end1.y;

		/* Compute r3 and r4.
		 */


		r3 = a1 * start2.x + b1 * start2.y + c1;
		r4 = a1 * end2.x + b1 * end2.y + c1;

		/* Check signs of r3 and r4.  If both point 3 and point 4 lie on
		 * same side of line 1, the line segments do not intersect.
		 */

		if ( r3 != 0 &&
			 r4 != 0 &&
			 SAME_SIGNS( r3, r4 ))
			return false;

		/* Compute a2, b2, c2 */

		a2 = end2.y - start2.y;
		b2 = start2.x - end2.y;
		c2 = end2.x * start2.y - start2.x * end2.y;

		/* Compute r1 and r2 */

		r1 = a2 * start1.x + b2 * start1.y + c2;
		r2 = a2 * end1.x + b2 * end1.y + c2;

		/* Check signs of r1 and r2.  If both point 1 and point 2 lie
		 * on same side of second line segment, the line segments do
		 * not intersect.
		 */

		if ( r1 != 0 &&
			 r2 != 0 &&
			 SAME_SIGNS( r1, r2 ))
			return false;

		/* Line segments intersect: compute intersection point. 
		 */

		denom = a1 * b2 - a2 * b1;
		if ( denom == 0 )
			return false;
		offset = denom < 0 ? - denom / 2 : denom / 2;

		/* The denom/2 is to get rounding instead of truncating.  It
		 * is added or subtracted to the numerator, depending upon the
		 * sign of the numerator.
		 */

		num = b1 * c2 - b2 * c1;
		intersectionPoint.x = ( num < 0 ? num - offset : num + offset ) / denom;

		num = a2 * c1 - a1 * c2;
		intersectionPoint.y = ( num < 0 ? num - offset : num + offset ) / denom;

		return true;
	}
}

#endif