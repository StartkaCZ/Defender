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
#include "Projectile.h"

#include <SFML/Graphics.hpp>


class Game : private sf::NonCopyable
{
public:
							Game();
	void					run();


private:
	void					loadContent();
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();

	void					updateStatistics(sf::Time elapsedTime);
	void					handleInput();

private:
	void					NukeReleased();

private:
	sf::RenderWindow		_window;
	sf::View				_worldView;
	sf::FloatRect			_worldBounds;

	sf::Text				_statisticsText;
	sf::Time				_statisticsUpdateTime;
	std::size_t				_statisticsNumFrames;

	TextureHolder			_textureHolder;
	FontHolder				_fontHolder;

	Player*					_player;
	std::vector<Projectile*>_projectiles;
	std::vector<Meteor*>	_meteors;
	std::vector<PowerUp*>	_powerUps;

	int						_score;

	const sf::Time			TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

#endif // BOOK_GAME_HPP