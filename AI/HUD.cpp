#include "HUD.h"

#include "StringHelpers.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::Initialize(sf::Texture& texture, sf::Font& font, int level, int score, int lives, int astronautsLeft)
{
	_hudSprite.setTexture(texture);

	_lives.setFont(font);
	_lives.setString("Lives: " + toString(lives));
	_lives.setPosition(sf::Vector2f(10, 150));
	_lives.setCharacterSize(20);

	_astronautsLeft.setFont(font);
	_astronautsLeft.setString("Astronauts: " + toString(astronautsLeft));
	_astronautsLeft.setPosition(sf::Vector2f(10, 170));
	_astronautsLeft.setCharacterSize(20);

	_score.setFont(font);
	_score.setString("Score: " + toString(score));
	_score.setPosition(sf::Vector2f(400, 160));
	_score.setCharacterSize(20);

	_level.setFont(font);
	_level.setString("Level: " + toString(level));
	_level.setPosition(sf::Vector2f(700, 160));
	_level.setCharacterSize(20);
}
void HUD::Update(float dt, int score, int lives, int astronautsLeft, sf::Vector2f position)
{
	_lives.setString("Lives: " + toString(lives));
	_lives.setPosition(position + sf::Vector2f(10, 150));

	_astronautsLeft.setString("Astronauts: " + toString(astronautsLeft));
	_astronautsLeft.setPosition(position + sf::Vector2f(10, 170));

	_score.setString("Score: " + toString(score));
	_score.setPosition(position + sf::Vector2f(325, 160));

	_level.setPosition(position + sf::Vector2f(700, 160));

	_hudSprite.setPosition(position);
}

void HUD::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_hudSprite);

	renderWindow.draw(_lives);
	renderWindow.draw(_level);
	renderWindow.draw(_score);
	renderWindow.draw(_astronautsLeft);
}
