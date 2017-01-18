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
#include "Interceptor.h"
#include "Bullet.h"
#include "Region.h"
#include "HUD.h"

#include <SFML/Graphics.hpp>


class Game : private sf::NonCopyable
{
private:
	enum class State
	{
		Menu,
		Game,
		GameOver,
	};

public:
								Game();
	void						run();


private:
	void						loadContent();
	void						processEvents();
	void						update(sf::Time elapsedTime);
	void						render();

	void						RestartGame();
	void						InitializeNewGame();
	void						NewLevel();

	void						updateStatistics(sf::Time elapsedTime);
	void						handleInput();

	void						UpdateMenu(sf::Time elapsedTime);
	void						UpdateGame(sf::Time elapsedTime);
	void						UpdateGameOver(sf::Time elapsedTime);

	void						UpdatePlayer(sf::Time elapsedTime);
	void						UpdateProjectiles(sf::Time elapsedTime);
	void						UpdateInterceptors(sf::Time elapsedTime);
	void						UpdateBullets(sf::Time elapsedTime);
	void						UpdateMeteors(sf::Time elapsedTime);
	void						UpdatePowerUps(sf::Time elapsedTime);
	void						UpdateAlienNests(sf::Time elapsedTime);
	void						UpdateAbductors(sf::Time elapsedTime);
	void						UpdateMutants(sf::Time elapsedTime);
	void						UpdateAstronauts(sf::Time elapsedTime);

	void						NukeReleased();

	void						SetupRegion(GameObject* gameObject);
	void						UpdateGameObjectBasedOnRegion(GameObject* gameObject);
	void						RemoveObjectFromRegion(GameObject* gameObject);

	void						UpdateCamera();

	void						DrawMenu();
	void						DrawGame();
	void						DrawGameOver();

	void						DrawVisibleRegions();
	void						DrawVisibleObjects();

	void						DrawRadar();
	void						DrawRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour);
	void						DrawCameraRectangle();

	void						Destroy();

private:
	sf::RenderWindow			_window;
	sf::View					_worldView;
	sf::FloatRect				_worldBounds;

	sf::Text					_statisticsText;
	sf::Time					_statisticsUpdateTime;
	std::size_t					_statisticsNumFrames;

	TextureHolder				_textureHolder;
	FontHolder					_fontHolder;

	HUD*						_hud;
	Player*						_player;
	std::vector<Bullet*>		_bullets;
	std::vector<Projectile*>	_projectiles;
	std::vector<Interceptor*>	_interceptors;
	std::vector<Meteor*>		_meteors;
	std::vector<PowerUp*>		_powerUps;
	std::vector<AlienNest*>		_nests;
	std::vector<Abductor*>		_abductors;
	std::vector<Mutant*>		_mutants;
	std::vector<Astronaut*>		_astronauts;
	std::vector<Region*>		_regions;

	int							_score;
	int							_level;

	int							_nestsToSpawn;
	int							_mutantsToSpawn;

	sf::Text					_indicationText;

	State						_state;

	const sf::Time				TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

#endif // BOOK_GAME_HPP