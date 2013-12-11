#pragma once

#ifndef AABB_H
#define AABB_H

#include<math.h>
#include <SFML/Graphics.hpp>
#include "LineSegment.h"

namespace SFMLTest
{
	class AABB : public sf::Drawable
	{
	public:
		AABB(){}
		AABB( const sf::Vector2f& p, const sf::Vector2f& e ):	P(p), E(e) 
		{
			updateSegments();
		}

		enum AABBSide
		{
			asTop = 0,
			asRight,
			asBottom,
			asLeft
		};

		void Move(sf::Vector2f movement)
		{
			P = P + movement;
			for(int i = 0; i < 4; i++)
			{
				lineSegments[i].Move(movement);
			}
			/*top.Move(movement);
			right.Move(movement);
			bottom.Move(movement);
			left.Move(movement);*/
		}

		//returns true if this is overlapping b
		const bool overlaps( const AABB& b ) const
		{
			const sf::Vector2f T = b.P - P;//vector from A to B
			bool rtn = fabs(T.x) <= ((E.x + b.E.x) / 2.0f) && fabs(T.y) <= ((E.y + b.E.y) / 2.0f);
			return	rtn;
		}

		//NOTE: since the vector indexing operator is not const,
		//we must cast away the const of the this pointer in the
		//following min() and max() functions
		//min x, y, or z
		const sf::Vector2f min() const
		{
			return sf::Vector2f( ((AABB*)this)->P.x - (((AABB*)this)->E.x / 2.0f),
								 ((AABB*)this)->P.y - (((AABB*)this)->E.y / 2.0f)
								);
		}

		//max x, y, or z
		const sf::Vector2f max() const
		{
			return sf::Vector2f( ((AABB*)this)->P.x + (((AABB*)this)->E.x / 2.0f),
								 ((AABB*)this)->P.y + (((AABB*)this)->E.y / 2.0f)
								);
		}

		//Accessors
		//(ish)
		const sf::Vector2f center() const
		{
			return sf::Vector2f(P.x + (E.x / 2.0f), P.y + (E.y / 2.0f));
		}

		const sf::Vector2f &Position() const {return P;}
		const sf::Vector2f &Extents() const {return E;}
		LineSegment Top() {return lineSegments[asTop];}
		LineSegment Right() {return lineSegments[asRight];}
		LineSegment Bottom() {return lineSegments[asBottom];}
		LineSegment Left() {return lineSegments[asLeft];}

		LineSegment GetSegment(AABBSide side) {return lineSegments[side];}

		/*struct SideIntersectionResults
		{
			LineSegment::IntersectionResults TopTop;
			LineSegment::IntersectionResults TopRight;
			LineSegment::IntersectionResults TopBottom;
			LineSegment::IntersectionResults TopLeft;

			LineSegment::IntersectionResults RightTop;
			LineSegment::IntersectionResults RightRight;
			LineSegment::IntersectionResults RightBottom;
			LineSegment::IntersectionResults RightLeft;

			LineSegment::IntersectionResults BottomTop;
			LineSegment::IntersectionResults BottomRight;
			LineSegment::IntersectionResults BottomBottom;
			LineSegment::IntersectionResults BottomLeft;

			LineSegment::IntersectionResults LeftTop;
			LineSegment::IntersectionResults LeftRight;
			LineSegment::IntersectionResults LeftBottom;
			LineSegment::IntersectionResults LeftLeft;
		};

		SideIntersectionResults CheckIntersections(AABB other)
		{
			SideIntersectionResults results;

			LineSegment otherTop = other.Top(), otherRight = other.Right(), otherBottom = other.Bottom(), otherLeft = other.Left();

			results.TopTop = top.IntersectsWith(otherTop);
			results.TopRight = top.IntersectsWith(otherRight);
			results.TopBottom = top.IntersectsWith(otherBottom);
			results.TopLeft = top.IntersectsWith(otherLeft);

			results.RightTop = right.IntersectsWith(otherTop);
			results.RightRight = right.IntersectsWith(otherRight);
			results.RightBottom = right.IntersectsWith(otherBottom);
			results.RightLeft = right.IntersectsWith(otherLeft);

			results.BottomTop = bottom.IntersectsWith(otherTop);
			results.BottomRight = bottom.IntersectsWith(otherRight);
			results.BottomBottom = bottom.IntersectsWith(otherBottom);
			results.BottomLeft = bottom.IntersectsWith(otherLeft);

			results.LeftTop = left.IntersectsWith(otherTop);
			results.LeftRight = left.IntersectsWith(otherRight);
			results.LeftBottom = left.IntersectsWith(otherBottom);
			results.LeftLeft = left.IntersectsWith(otherLeft);

			return results;
		}*/

		struct SideIntersectionResults
		{
			AABBSide thisSide;
			AABBSide otherSide;
			std::list<LineSegment::IntersectionResults> intersections;
		};

		SideIntersectionResults CheckIntersectionResults(AABB other)
		{
			SideIntersectionResults results;

			for(int thisSideCounter = 0; thisSideCounter < 4; thisSideCounter++)
			{
				LineSegment thisSide = lineSegments[thisSideCounter];
				for(int otherSideCounter = 0; otherSideCounter < 4; otherSideCounter++)
				{
					//We will never collide with the same side of the opposite aabb
					if(otherSideCounter == thisSideCounter)
						continue;

					LineSegment otherSide = other.GetSegment((AABBSide)otherSideCounter);

					LineSegment::IntersectionResults intersectionResults = thisSide.IntersectsWith(otherSide);

					//No intersection with this side
					if(intersectionResults.intersectionType == LineSegment::IntersectionType::None)
						continue;

					//If these sides are opposites and they overlap, then that's our collision
					if
					(
						(otherSideCounter == (thisSideCounter + 2) || otherSideCounter == (thisSideCounter - 2))
						&&
						intersectionResults.intersectionType == LineSegment::IntersectionType::Overlap
					)
					{
						results.intersections.push_back(intersectionResults);
						results.otherSide = (AABBSide)otherSideCounter;
						results.thisSide = (AABBSide)thisSideCounter;
						return results;
					}
					
					results.intersections.push_back(intersectionResults);
				}
			}

			return results;
			//if(
		}

		/*Idea: Find which line segments intersect on a collision, then calculate the time an overlap would 
				happen between the segments.  The shortest time is the actual side that collides
				-Check opposites: top1 vs bottom2, left1 vs right2, etc.
		*/

		//Setters
		void setPosition(sf::Vector2f newPosition)
		{
			P = newPosition;
			updateSegments();
		}

		void setExtents(sf::Vector2f newExtents)
		{
			E = newExtents;
			updateSegments();
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(lineSegments[asTop], states);
			target.draw(lineSegments[asRight], states);
			target.draw(lineSegments[asBottom], states);
			target.draw(lineSegments[asLeft], states);
		}

	private:
		sf::Vector2f P; //position
		sf::Vector2f E; //x,y,z extents

		LineSegment lineSegments[4];
		/*LineSegment top;
		LineSegment right;
		LineSegment bottom;
		LineSegment left;*/

		void updateSegments()
		{
			sf::Vector2f topLeft = sf::Vector2f(P.x - (E.x / 2), P.y - (E.y / 2));
			sf::Vector2f topRight = sf::Vector2f(P.x + (E.x / 2), topLeft.y);
			sf::Vector2f bottomRight = sf::Vector2f(topRight.x, P.y + (E.y / 2));
			sf::Vector2f bottomLeft = sf::Vector2f(topLeft.x, bottomRight.y);
			lineSegments[asTop] = LineSegment(topLeft, topRight);
			lineSegments[asRight]= LineSegment(topRight, bottomRight);
			lineSegments[asBottom] = LineSegment(bottomRight, bottomLeft);
			lineSegments[asLeft] = LineSegment(topLeft, bottomLeft);
		}

		AABBSide GetCollidingSide(AABB other, 
								  AABBSide ourSide,
								  AABBSide otherSide,
								  LineSegment::IntersectionResults &intersectionResults)
		{
			switch(ourSide)
			{
			case asTop:
				{
					switch(otherSide)
					{
					case asRight:
						{
							//Check Left and Bottom
							//intersectionResults = other.GetSegment(as
						}
						break;
					case asBottom:
						{
							//Check left and Right
						}
						break;
					case asLeft:
						{
							//Check right and bottom
						}
						break;
					}
				}
				break;
			case asRight:
				{
					switch(otherSide)
					{
					case asTop:
						{
						}
						break;
					case asBottom:
						{
						}
						break;
					case asLeft:
						{
						}
						break;
					}
				}
				break;
			case asBottom:
				{
					switch(otherSide)
					{
					case asRight:
						{
						}
						break;
					case asTop:
						{
						}
						break;
					case asLeft:
						{
						}
						break;
					}
				}
				break;
			case asLeft:
				{
					switch(otherSide)
					{
					case asRight:
						{
						}
						break;
					case asBottom:
						{
						}
						break;
					case asTop:
						{
						}
						break;
					}
				}
				break;
			}
		}
	};
};

#endif