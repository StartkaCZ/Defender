#include "HUD.h"

#include "StringHelpers.h"

#include "ConstHolder.h"

HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::Initialize(TextureHolder& textureHolder, sf::Font& font, int level, int score, int astronautsLeft, int enemiesLeft, Player*& player)
{
	_player = player;

	_hudSprite.setTexture(textureHolder.get(Textures::ID::HUD));

	//SETUP FOR SPRITES
	SetupSprite(_lifesSprite, textureHolder.get(Textures::ID::Player), sf::Vector2f(10, HUD_HEIGHT - 70), ICON_SCALE, true);
	SetupSprite(_astronautsSprite, textureHolder.get(Textures::ID::Astronaut), sf::Vector2f(10, HUD_HEIGHT - 47.5f), ICON_SCALE, true);
	SetupSprite(_superJumpsSprite, textureHolder.get(Textures::ID::PowerUp_SuperJump), sf::Vector2f(10, HUD_HEIGHT - 25), ICON_SCALE, true);

	SetupSprite(_nukeSprite, textureHolder.get(Textures::ID::IconNuke), sf::Vector2f(250, HUD_HEIGHT - 47.5f), 1, _player->canNuke());
	SetupSprite(_rapidFireSprite, textureHolder.get(Textures::ID::PowerUp_RapidFire), sf::Vector2f(500, HUD_HEIGHT - 47.5f), 1, _player->rapidFire());
	SetupSprite(_shieldSprite, textureHolder.get(Textures::ID::PowerUp_Shield), sf::Vector2f(750, HUD_HEIGHT - 47.5f), 1, _player->shieldOn());

	//SETUP FOR TEXTS
	SetupText(_lifesText, font, sf::Vector2f(50, HUD_HEIGHT - 70), 14, "x", _player->getLives());
	SetupText(_astronautsLeftText, font, sf::Vector2f(50, HUD_HEIGHT - 47.5f), 14, "x", astronautsLeft);
	SetupText(_superJumpsLeftText, font, sf::Vector2f(50, HUD_HEIGHT - 25), 14, "x", _player->getSuperJumps());

	SetupText(_levelText, font, sf::Vector2f(1000, HUD_HEIGHT - 70), 14, "Level: ", level);
	SetupText(_scoreText, font, sf::Vector2f(1000, HUD_HEIGHT - 47.5f), 14, "Score: ", score);
	SetupText(_enemiseLeftText, font, sf::Vector2f(1000, HUD_HEIGHT - 25), 14, "Enemies: ", enemiesLeft);
}
void HUD::SetupSprite(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f position, float scale, bool on)
{
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	sprite.setPosition(position);

	if (on)
	{
		_nukeSprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		_nukeSprite.setColor(sf::Color(75, 75, 75, 255));
	}
}
void HUD::SetupText(sf::Text& text, sf::Font& font, sf::Vector2f position, unsigned int size, std::string message, int value)
{
	text.setFont(font);
	text.setString(message + toString(value));
	text.setPosition(position);
	text.setCharacterSize(size);
}


void HUD::Update(float dt, int score, int astronautsLeft, int enemiesLeft, int level, sf::Vector2f position)
{
	_hudSprite.setPosition(position);

	//Update FOR SPRITES
	UpdateSprite(_lifesSprite, position + sf::Vector2f(10, HUD_HEIGHT - 70), true);
	UpdateSprite(_astronautsSprite, position + sf::Vector2f(10, HUD_HEIGHT - 47.5f), true);
	UpdateSprite(_superJumpsSprite, position + sf::Vector2f(10, HUD_HEIGHT - 25), true);

	UpdateSprite(_nukeSprite, position + sf::Vector2f(250, HUD_HEIGHT - 47.5f), _player->canNuke());
	UpdateSprite(_shieldSprite, position + sf::Vector2f(750, HUD_HEIGHT - 47.5f), _player->shieldOn());
	UpdateSprite(_rapidFireSprite, position + sf::Vector2f(500, HUD_HEIGHT - 47.5f), _player->rapidFire());

	//Update FOR TEXTS
	UpdateText(_lifesText, position + sf::Vector2f(50, HUD_HEIGHT - 70), "x", _player->getLives());
	UpdateText(_astronautsLeftText, position + sf::Vector2f(50, HUD_HEIGHT - 47.5f), "x", astronautsLeft);
	UpdateText(_superJumpsLeftText, position + sf::Vector2f(50, HUD_HEIGHT - 25), "x", _player->getSuperJumps());

	UpdateText(_levelText, position + sf::Vector2f(1000, HUD_HEIGHT - 70), "Level: ", level);
	UpdateText(_scoreText, position + sf::Vector2f(1000, HUD_HEIGHT - 47.5f), "Score: ", score);
	UpdateText(_enemiseLeftText, position + sf::Vector2f(1000, HUD_HEIGHT - 25), "Enemies: ", enemiesLeft);
}
void HUD::UpdateSprite(sf::Sprite& sprite, sf::Vector2f position, bool on)
{
	sprite.setPosition(position);

	if (on)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		sprite.setColor(sf::Color(75, 75, 75, 255));
	}
}
void HUD::UpdateText(sf::Text& text, sf::Vector2f position, std::string message, int value)
{
	text.setString(message + toString(value));
	text.setPosition(position);
}


void HUD::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_hudSprite);

	renderWindow.draw(_lifesSprite);
	renderWindow.draw(_astronautsSprite);
	renderWindow.draw(_superJumpsSprite);

	renderWindow.draw(_shieldSprite);
	renderWindow.draw(_rapidFireSprite);
	renderWindow.draw(_nukeSprite);

	renderWindow.draw(_lifesText);
	renderWindow.draw(_astronautsLeftText);
	renderWindow.draw(_superJumpsLeftText);

	renderWindow.draw(_levelText);
	renderWindow.draw(_scoreText);
	renderWindow.draw(_enemiseLeftText);
}
