#pragma once
#include <SFML/Graphics.hpp>
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
};