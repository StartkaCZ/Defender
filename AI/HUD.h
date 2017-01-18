#pragma once

#include "SFML\Graphics.hpp"

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include "Player.h"

class HUD : private sf::NonCopyable
{
	enum class SpriteID
	{

	};

public:
				HUD();
				~HUD();

	void		Initialize(TextureHolder& textureHolder, sf::Font& font, int level, int score, int astronautsLeft, int enemiesLeft, Player*& player);
	void		Update(float dt, int score, int astronautsLeft, int enemiesLeft, int level, sf::Vector2f position);

	void		Draw(sf::RenderWindow& renderWindow);

private:
	void		SetupSprite(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f position, float scale, bool on);
	void		SetupText(sf::Text& text, sf::Font& font, sf::Vector2f position, unsigned int size, std::string message, int value);

	void		UpdateSprite(sf::Sprite& sprite, sf::Vector2f position, bool on);
	void		UpdateText(sf::Text& text, sf::Vector2f position, std::string message, int value);

private:
	sf::Sprite	_hudSprite;

	sf::Sprite	_lifesSprite;
	sf::Sprite	_astronautsSprite;
	sf::Sprite	_superJumpsSprite;
	sf::Sprite	_shieldSprite;
	sf::Sprite	_rapidFireSprite;
	sf::Sprite	_nukeSprite;

	sf::Text	_lifesText;
	sf::Text	_astronautsLeftText;
	sf::Text	_superJumpsLeftText;

	sf::Text	_scoreText;
	sf::Text	_levelText;
	sf::Text	_enemiseLeftText;

	Player*		_player;
};

