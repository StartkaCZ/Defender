#ifndef GAME_H
#define GAME_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include "Player.h"
#include "Abductor.h"
#include "Mutant.h"
#include "AlienNest.h"
#include "Astronaut.h"
#include "Flock.h"
#include "Meteor.h"
#include "PowerUp.h"
#include "Projectile.h"
#include "Interceptor.h"
#include "Region.h"

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
	void					UpdateProjectiles(sf::Time elapsedTime);
	void					UpdateInterceptors(sf::Time elapsedTime);
	void					UpdateMeteors(sf::Time elapsedTime);
	void					UpdatePowerUps(sf::Time elapsedTime);
	void					UpdateAlienNests(sf::Time elapsedTime);
	void					UpdateAbductors(sf::Time elapsedTime);
	//void					UpdateMutants(sf::Time elapsedTime);
	void					UpdateAstronauts(sf::Time elapsedTime);

	void					NukeReleased();

	void					DrawProjectiles();
	void					DrawInterceptors();
	void					DrawMeteors();
	void					DrawPowerUps();
	void					DrawAlienNests();
	void					DrawAbductors();
	//void					DrawMutants();
	void					DrawAstronauts();

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
	std::vector<Astronaut*>	_astronauts;
	std::vector<Projectile*>_projectiles;
	std::vector<Interceptor*>_interceptors;
	std::vector<Meteor*>	_meteors;
	std::vector<PowerUp*>	_powerUps;
	std::vector<AlienNest*>	_nests;
	std::vector<Abductor*>	_abductors;
	//Create flock, vector of shapes, and initialize boids
	Flock flock;

	std::vector<Region*>	_regions;

	int						_score;

	const sf::Time			TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

#endif // BOOK_GAME_HPP