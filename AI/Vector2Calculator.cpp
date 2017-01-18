#include "Vector2Calculator.h"

void Vector2Calculator::Normalize(sf::Vector2f& a)
{
	float lenght = Lenght(a);

	if (lenght != 0)
	{
		a.x /= lenght;
		a.y /= lenght;
	}
}

sf::Vector2f Vector2Calculator::Subtract(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f newVector = sf::Vector2f(b.x - a.x, b.y - a.y);
	return newVector;
}

sf::Vector2f Vector2Calculator::Add(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f newVector = sf::Vector2f(b.x + a.x, b.y + a.y);
	return newVector;
}

float Vector2Calculator::Lenght(sf::Vector2f a)
{
	return sqrt((a.x*a.x) + (a.y * a.y));
}
float Vector2Calculator::Distance(sf::Vector2f a, sf::Vector2f b)
{
	float abX = b.x - a.x;
	float abY = b.y - a.y;

	return sqrt((abX*abX) + (abY*abY));
}
