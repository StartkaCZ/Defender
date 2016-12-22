#include "Interceptor.h"
#include "ConstHolder.h"
#include "Vector2Calculator.h"

Interceptor::Interceptor(int& parentRocketCounter)
	: _parentRocketCounter(parentRocketCounter)
{
}

Interceptor::~Interceptor()
{
}

void Interceptor::initialize(sf::Vector2f position, sf::Texture &texture, sf::Vector2f target, sf::Vector2u screenSize)
{

}

void Interceptor::Update(float dt, sf::Vector2f playerPosition)
{

}
void Interceptor::CalculateVelocity(sf::Vector2f playerPosition)
{
	sf::Vector2f target = playerPosition - getPosition();
}
