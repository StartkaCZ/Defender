#pragma once

#include "SFML\Graphics.hpp"

class HUD : private sf::NonCopyable
{
public:
				HUD();
				~HUD();

	void		Initialize(sf::Texture& texture, sf::Font& font, int level, int score, int lives, int astronautsLeft);
	void		Update(float dt, int score, int lives, int astronautsLeft, sf::Vector2f position);

	void		Draw(sf::RenderWindow& renderWindow);

private:
	sf::Sprite	_hudSprite;

	sf::Text	_lives;
	sf::Text	_astronautsLeft;
	sf::Text	_score;
	sf::Text	_level;
};

