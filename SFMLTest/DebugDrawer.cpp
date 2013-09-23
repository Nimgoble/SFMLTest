#include "DebugDrawer.h"
/*#include "ConversionHelpers.h"
using namespace SFMLTest;

void DebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setPointCount(vertexCount);
	for (int i = 0; i < vertexCount; i++) 
	{
		sf::Vector3f point = B2VecToSFMLVec(vertices[i]);
		shape.setPoint(i, point);
    }

	shape.setFillColor(sf::Color::Red);
	target->draw(shape);
}
void DebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setPointCount(vertexCount);
	for (int i = 0; i < vertexCount; i++) 
	{
		sf::Vector3f point = B2VecToSFMLVec(vertices[i]);
		shape.setPoint(i, point);
    }

	shape.setFillColor(sf::Color::Red);
	target->draw(shape);
}
void DebugDrawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape shape(radius);
	shape.setPosition(B2VecToSFMLVec(center));
	target->draw(shape);
}
void DebugDrawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape shape(radius);
	shape.setPosition(B2VecToSFMLVec(center));
	target->draw(shape);
}
void DebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::RectangleShape shape;
	shape.
}
void DebugDrawer::DrawTransform(const b2Transform& xf)
{
	sf::RectangleShape shape(sf::Vector3f(1.0f, 1.0f));
	shape.setPosition(B2VecToSFMLVec(xf.p));
	shape.setFillColor(sf::Color::White);
	target->draw(shape);
}*/