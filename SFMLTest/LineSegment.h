#pragma once

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "SFML\Graphics.hpp"
#include <cfloat>

namespace SFMLTest
{
	class LineSegment : public sf::Drawable
	{
	public:
		LineSegment()
		{
		}

		LineSegment(sf::Vector2f _start, sf::Vector2f _end)
		{
			start = _start;
			end = _end;
			slope = CalculateSlope(start, end);
			line[0] = sf::Vertex(start);
			line[1] = sf::Vertex(end);
		}

		enum IntersectionType
		{
			None,
			Intersection,
			Overlap
		};

		struct IntersectionResults
		{
			sf::Vector2f intersectionPoint;
			IntersectionType intersectionType;
		};

		IntersectionResults IntersectsWith(LineSegment other)
		{
			IntersectionResults results;
			sf::Vector2f I0, I1;
			int rtn = intersect2D_2Segments(*this, other, &I0, &I1);
			switch(rtn)
			{
			case 0:
				results.intersectionType = IntersectionType::None;
				break;
			case 1:
				results.intersectionType = IntersectionType::Intersection;
				results.intersectionPoint = I0;
				break;
			case 2:
				results.intersectionType = IntersectionType::Overlap;
				results.intersectionPoint = I0;
				break;
			}
			
			return results;
			
			float s, t;
			const sf::Vector2f otherSlope = other.Slope();
			const sf::Vector2f otherStart = other.Start();
			const sf::Vector2f otherEnd = other.End();
			float divisor = (-otherSlope.x * slope.y + slope.x * otherSlope.y);
			//Collinear? Need epsilon
			if(FloatEqualToZero(divisor))
			{
				if(PointOnLine(otherStart) || PointOnLine(otherEnd))
				{
					results.intersectionPoint.x = results.intersectionPoint.y = 0.0f;
					results.intersectionType = IntersectionType::Overlap;
					return results;
				}
				else
					return results;
			}


			s = (-slope.y * (start.x - otherStart.x) + slope.x * (start.y - otherStart.y)) / divisor;
			t = (otherSlope.x * (start.y - otherStart.y) - otherSlope.y * (start.x - otherStart.x)) / divisor;

			if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
			{
				//Collision
				results.intersectionPoint.x = start.x + (t * slope.x);
				results.intersectionPoint.y = start.y + (t * slope.y);
				results.intersectionType = IntersectionType::Intersection;
				return results;
			}

			return results;
		}

		//Does the given point lie on this line segment?
		bool PointOnLine(sf::Vector2f point)
		{
			return (Collinear(point) && ((slope.x == 0) ? WithinX(point.x) : WithinY(point.y)));
		}

		//Is the given point collinear with this segment?
		bool Collinear(sf::Vector2f point)
		{
			return ((end.x - start.x) * (point.y - start.y) == (point.x - start.x) * (end.y - start.y));
		}

		//Accessors
		const sf::Vector2f Start() {return start;};
		const sf::Vector2f End() {return end;};
		const sf::Vector2f Slope() {return slope;};

		//Shift the line
		void Move(sf::Vector2f movement)
		{
			start = start + movement;
			end = end + movement;
			line[0].position = start;
			line[1].position = end;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(line, 2, sf::Lines, states);
		}

	private:
		sf::Vector2f start;
		sf::Vector2f end;
		sf::Vector2f slope;

		sf::Vertex line[2];
		
		//To be honest: no idea what this shit does.
		bool WithinX(float var)
		{
			return Within(start.x, var, end.x);
		}

		bool WithinY(float var)
		{
			return Within(start.y, var, end.y);
		}

		bool Within(float p, float q, float r)
		{
			return ((p <= q <= r) || (r <= q <= p));
		}

		//Static stuff
	protected:
		//Because why the fuck not?
		static sf::Vector2f CalculateSlope(const sf::Vector2f &start, const sf::Vector2f &end)
		{
			return sf::Vector2f((end.x - start.x), (end.y - start.y));
		}

		//Epsilon comparison
		static bool FloatEqualToZero(const float &a)
		{
			return (fabs(a) <= FLT_EPSILON);
		}

		#define SMALL_NUM   0.00000001 // anything that avoids division overflow
		// dot product (3D) which allows vector operations in arguments
		//#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
		#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y)
		#define perp(u,v)  ((u).x * (v).y - (u).y * (v).x)  // perp product  (2D)

		// intersect2D_2Segments(): find the 2D intersection of 2 finite segments
		//    Input:  two finite segments S1 and S2
		//    Output: *I0 = intersect point (when it exists)
		//            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
		//    Return: 0=disjoint (no intersect)
		//            1=intersect  in unique point I0
		//            2=overlap  in segment from I0 to I1
		static int intersect2D_2Segments( LineSegment S1, LineSegment S2, sf::Vector2f* I0, sf::Vector2f* I1 )
		{
			sf::Vector2f    u = S1.End() - S1.Start();
			sf::Vector2f    v = S2.End() - S2.Start();
			sf::Vector2f    w = S1.Start() - S2.Start();
			float     D = perp(u,v);

			// test if  they are parallel (includes either being a point)
			if (fabs(D) < SMALL_NUM) 
			{           // S1 and S2 are parallel
				if (perp(u,w) != 0 || perp(v,w) != 0)  
				{
					return 0;                    // they are NOT collinear
				}
				// they are collinear or degenerate
				// check if they are degenerate  points
				float du = dot(u,u);
				float dv = dot(v,v);
				if (du==0 && dv==0) 
				{            // both segments are points
					if (S1.Start() !=  S2.Start())         // they are distinct  points
						 return 0;
					*I0 = S1.Start();                 // they are the same point
					return 1;
				}
				if (du==0) 
				{                     // S1 is a single point
					if  (inSegment(S1.Start(), S2) == 0)  // but is not in S2
						 return 0;
					*I0 = S1.Start();
					return 1;
				}
				if (dv==0) 
				{                     // S2 a single point
					if  (inSegment(S2.Start(), S1) == 0)  // but is not in S1
						 return 0;
					*I0 = S2.Start();
					return 1;
				}
				// they are collinear segments - get  overlap (or not)
				float t0, t1;                    // endpoints of S1 in eqn for S2
				sf::Vector2f w2 = S1.End() - S2.Start();
				if (v.x != 0) 
				{
						 t0 = w.x / v.x;
						 t1 = w2.x / v.x;
				}
				else 
				{
						 t0 = w.y / v.y;
						 t1 = w2.y / v.y;
				}
				if (t0 > t1) 
				{                   // must have t0 smaller than t1
						 float t=t0; t0=t1; t1=t;    // swap if not
				}
				if (t0 > 1 || t1 < 0) 
				{
					return 0;      // NO overlap
				}
				t0 = t0<0? 0 : t0;               // clip to min 0
				t1 = t1>1? 1 : t1;               // clip to max 1
				if (t0 == t1) 
				{                  // intersect is a point
					*I0 = S2.Start() +  t0 * v;
					return 1;
				}

				// they overlap in a valid subsegment
				*I0 = S2.Start() + t0 * v;
				*I1 = S2.Start() + t1 * v;
				return 2;
			}

			// the segments are skew and may intersect in a point
			// get the intersect parameter for S1
			float     sI = perp(v,w) / D;
			if (sI < 0 || sI > 1)                // no intersect with S1
				return 0;

			// get the intersect parameter for S2
			float     tI = perp(u,w) / D;
			if (tI < 0 || tI > 1)                // no intersect with S2
				return 0;

			*I0 = S1.Start() + sI * u;                // compute S1 intersect point
			return 1;
		}
		//===================================================================
 


		// inSegment(): determine if a point is inside a segment
		//    Input:  a point P, and a collinear segment S
		//    Return: 1 = P is inside S
		//            0 = P is  not inside S
		static int inSegment( sf::Vector2f P, LineSegment S)
		{
			if (S.Start().x != S.End().x) 
			{    // S is not  vertical
				if (S.Start().x <= P.x && P.x <= S.End().x)
					return 1;
				if (S.Start().x >= P.x && P.x >= S.End().x)
					return 1;
			}
			else 
			{    // S is vertical, so test y  coordinate
				if (S.Start().y <= P.y && P.y <= S.End().y)
					return 1;
				if (S.Start().y >= P.y && P.y >= S.End().y)
					return 1;
			}
			return 0;
		}
		//===================================================================
	};
};
#endif