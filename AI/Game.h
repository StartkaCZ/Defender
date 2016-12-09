#ifndef GAME_H
#define GAME_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Player.h"
#include "Alien.h"

#include <SFML/Graphics.hpp>
#include <memory>


class Game : private sf::NonCopyable
{
public:
	Game();
	void					run();


private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();

	void					updateStatistics(sf::Time elapsedTime);
	void					handlePlayerInput();


private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture				mTexture;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;

	TextureHolder			_textureHolder;
	std::unique_ptr<Player>	_player;
	std::unique_ptr<Alien>	_alien1;
	std::unique_ptr<Alien>	_alien2;
};

#endif // BOOK_GAME_HPP