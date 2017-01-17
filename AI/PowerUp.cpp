#include "PowerUp.h"
#include "ConstHolder.h"


PowerUp::PowerUp()
{
}


PowerUp::~PowerUp()
{
}

void PowerUp::Initialize(sf::Texture &texture, ObjectType type, sf::FloatRect screenRectangle)
{
	sf::Vector2f size = sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
	sf::Vector2u screenSize = sf::Vector2u(screenRectangle.width, screenRectangle.height);

	float x = (rand() % screenSize.x - size.x - size.x - size.x) + size.x;
	float y = (rand() % screenSize.y * PLAYER_OFFSET_FROM_GROUND - size.y - size.y - size.y) + size.y;

	GameObject::initialize(sf::Vector2f(x, y), texture, type);

	_isAlive = true;
}

void PowerUp::Update(float dt)
{

}

void PowerUp::CollisionEnter(GameObject*& objectCollided)
{
	if (objectCollided->getType() == ObjectType::Player)
	{
		Die();
	}
}

void PowerUp::Die()
{
	_isAlive = false;
}

bool PowerUp::getAlive() const
{
	return _isAlive;
}
