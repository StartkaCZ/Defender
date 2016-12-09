#ifndef GAME_H
#define GAME_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include "Player.h"
#include "Abductor.h"
#include "Mutant.h"
#include "AlienNest.h"
#include "Astronaut.h"
#include "Meteor.h"
#include "PowerUp.h"

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
	void					handleInput();


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
};

#endif // BOOK_GAME_HPP