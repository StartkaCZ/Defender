#pragma once

#include <SFML/Graphics.hpp>


class Vector2Calculator
{
public:
	static void Normalize(sf::Vector2f& a);

	static sf::Vector2f Subtract(sf::Vector2f a, sf::Vector2f b);
	static sf::Vector2f Add(sf::Vector2f a, sf::Vector2f b);

	static float Lenght(sf::Vector2f a);
	static float Distance(sf::Vector2f a, sf::Vector2f b);
};

