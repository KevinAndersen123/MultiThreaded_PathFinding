#pragma once
#include <SFML/Graphics.hpp>
#include <assert.h>
class Thor
{
public:
	template <typename T>
	static T length(const sf::Vector2<T>& vector)
	{
		return sqrt(squaredLength(vector));
	}

	template <typename T>
	static T squaredLength(const sf::Vector2<T>& vector)
	{
		return dotProduct(vector, vector);
	}

	template <typename T>
	static T dotProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template <typename T>
	static sf::Vector2<T> unitVector(const sf::Vector2<T>& vector)
	{
		assert(vector != sf::Vector2<T>());
		return vector / length(vector);
	}

	template <typename T>
	static T polarAngle(const sf::Vector2<T>& vector)
	{
		assert(vector != sf::Vector2<T>());
		return arcTan2(vector.y, vector.x);
	}

	typedef double Type;
	static Type pi() { return 3.141592653589793238462643383; }
	static Type radToDeg(Type rad) 
	{
		return 180 / pi() * rad;
	}
	static Type arcTan2(Type valY, Type valX) { return radToDeg(std::atan2(valY, valX)); }
};