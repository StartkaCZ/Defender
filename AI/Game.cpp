#include "Game.h"
#include "StringHelpers.h"

#include "ConstHolder.h"
#include "CollisionManager.h"

Game::Game()
	: _window(sf::VideoMode(800, 600), "Defender", sf::Style::Close)
	, _worldView(_window.getDefaultView())
	, _worldBounds(0.f, 0.f, _worldView.getSize().x * SCREEN_TIME_SIZE, _worldView.getSize().y)
	, _textureHolder()
	, _player(nullptr)
	, _projectiles(std::vector<Projectile*>())
	, _interceptors(std::vector<Interceptor*>())
	, _bullets(std::vector<Bullet*>())
	, _meteors(std::vector<Meteor*>())
	, _powerUps(std::vector<PowerUp*>())
	, _nests(std::vector<AlienNest*>())
	, _abductors(std::vector<Abductor*>())
	, _mutants(std::vector<Mutant*>())
	, _regions(std::vector<Region*>())
	, _statisticsText()
	, _statisticsUpdateTime()
	, _statisticsNumFrames(0)
	, _score(0)
{
	loadContent();


	while (_mutants.size() < 3)
	{

		Mutant* mutant = new Mutant(_bullets, _textureHolder.get(Textures::ID::Projectile_Interceptor));

		float x = (rand() % (int)_worldBounds.width - 60) + 30;
		float y = (rand() % (int)_worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 60) + 30;

		mutant->initialize(sf::Vector2f(x,y), _textureHolder.get(Textures::ID::Mutant), _worldBounds);

		_mutants.push_back(mutant);
	}
	while (_astronauts.size() < 5)
	{
		Astronaut* astronaut = new Astronaut();
		astronaut->Initialize(sf::Vector2f(800, 200), _textureHolder.get(Textures::ID::Astronaut));

		_astronauts.push_back(astronaut);
	}
	/*
	while (_meteors.size() < MAX_METEORS)
	{
		Meteor* meteor = new Meteor();

		meteor->Initialize(_textureHolder.get(Textures::ID::Obstacle_Meteor), _worldBounds);

		_meteors.push_back(meteor);
	}

	while (_powerUps.size() < MAX_POWER_UPS)
	{
		PowerUp* powerUp = new PowerUp();

		powerUp->Initialize(_textureHolder.get(Textures::ID::PowerUp_SuperJump), ObjectType::PowerUp_SuperJump, _worldBounds);

		_powerUps.push_back(powerUp);
	}
	*/
	while (_nests.size() < 2)
	{
		AlienNest* nest = new AlienNest(_interceptors, _abductors, _bullets, _textureHolder.get(Textures::ID::Projectile_Interceptor), _textureHolder.get(Textures::ID::Abductor), _textureHolder.get(Textures::ID::Projectile_Interceptor));

		float x = (rand() % (int)_worldBounds.width - 60) + 30;
		float y = (rand() % (int)_worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 60) + 30;

		nest->Initialize(sf::Vector2f(x, y), _textureHolder.get(Textures::ID::AlienNest), _worldBounds);

		_nests.push_back(nest);
	}

	for (int i = 0; _regions.size() < SCREEN_TIME_SIZE; i++)
	{
		Region* region = new Region();

		region->Initialize(sf::Vector2f(i * _worldView.getSize().x, 0), _textureHolder.get(Textures::ID::Background), _textureHolder.get(Textures::ID::Foreground));

		_regions.push_back(region);
	}

	_player = new Player(_projectiles, _textureHolder.get(Textures::ID::Projectile_PlayerLazer));
	_player->Initialize(sf::Vector2f(_worldBounds.width * 0.5f, _worldBounds.height * 0.5f), _textureHolder.get(Textures::ID::Player), _worldBounds);
	_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldBounds.height * 0.5f));

	_statisticsText.setFont(_fontHolder.get(Fonts::ID::Normal));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);


	

}

void Game::loadContent()
{
	_textureHolder.load(Textures::ID::Player, "Media/Textures/Player.png");
	_textureHolder.load(Textures::ID::Projectile_PlayerLazer, "Media/Textures/bullet.png");

	_textureHolder.load(Textures::ID::Astronaut, "Media/Textures/Astronaut.png");

	_textureHolder.load(Textures::ID::Abductor, "Media/Textures/Abductor.png");

	_textureHolder.load(Textures::ID::AlienNest, "Media/Textures/AlienNest.png");
	_textureHolder.load(Textures::ID::Projectile_Interceptor, "Media/Textures/Interceptor.png");

	_textureHolder.load(Textures::ID::Mutant, "Media/Textures/Mutant.png");

	_textureHolder.load(Textures::ID::Obstacle_Meteor, "Media/Textures/Meteor.png");

	_textureHolder.load(Textures::ID::PowerUp_SuperJump, "Media/Textures/SuperJumpPowerUp.png");

	_textureHolder.load(Textures::ID::Background, "Media/Textures/Background.png");

	_textureHolder.load(Textures::ID::Foreground, "Media/Textures/Foreground.png");

	_fontHolder.load(Fonts::ID::Normal, "Media/Sansation.ttf");
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(TIME_PER_FRAME);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		handleInput();

		switch (event.type)
		{
			case sf::Event::Closed:
				_window.close();
				break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	CollisionManager::Instance()->CheckForCollisions(_player, _projectiles, _interceptors, _powerUps, _meteors, _nests, _abductors,_astronauts);

	_player->Update(elapsedTime.asSeconds());
	if (_player->hasNuked())
	{
		NukeReleased();
		_player->NukingOver();
	}

	_score++;

	UpdateProjectiles(elapsedTime);
	UpdateInterceptors(elapsedTime);
	UpdateBullets(elapsedTime);

	UpdateMeteors(elapsedTime);

	UpdatePowerUps(elapsedTime);
	UpdateAlienNests(elapsedTime);
	UpdateAbductors(elapsedTime);
	UpdateMutants(elapsedTime);
	UpdateAstronauts(elapsedTime);

	_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldView.getCenter().y));
}

#pragma region UpdateMethods

void Game::UpdateProjectiles(sf::Time elapsedTime)
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		if (_projectiles[i]->getAlive())
		{
			_projectiles[i]->Update(elapsedTime.asSeconds());
		}
		else
		{
			delete _projectiles[i];
			_projectiles.erase(_projectiles.begin() + i);
			i--;
		}
	}
}
void Game::UpdateInterceptors(sf::Time elapsedTime)
{
	for (int i = 0; i < _interceptors.size(); i++)
	{
		if (_interceptors[i]->getAlive())
		{
			_interceptors[i]->Update(elapsedTime.asSeconds(), _player->getPosition());
		}
		else
		{
			delete _interceptors[i];
			_interceptors.erase(_interceptors.begin() + i);
			i--;
		}
	}
}

void Game::UpdateBullets(sf::Time elapsedTime)
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		if (_bullets[i]->getAlive())
		{
			_bullets[i]->Update(elapsedTime.asSeconds());
		}
		else
		{
			delete _bullets[i];
			_bullets.erase(_bullets.begin() + i);
			i--;
		}
	}
}

void Game::UpdateMeteors(sf::Time elapsedTime)
{
	for (int i = 0; i < _meteors.size(); i++)
	{
		if (_meteors[i]->getAlive())
		{
			_meteors[i]->Update(elapsedTime.asSeconds());
		}
		else
		{
			_meteors[i]->Restart();
		}
	}
}
void Game::UpdatePowerUps(sf::Time elapsedTime)
{
	for (int i = 0; i < _powerUps.size(); i++)
	{
		if (_powerUps[i]->getAlive())
		{
			_powerUps[i]->Update(elapsedTime.asSeconds());
		}
		else
		{
			delete _powerUps[i];
			_powerUps.erase(_powerUps.begin() + i);
			i--;
		}
	}
}
void Game::UpdateAlienNests(sf::Time elapsedTime)
{
	for (int i = 0; i < _nests.size(); i++)
	{
		if (_nests[i]->getAlive())
		{
			_nests[i]->Update(elapsedTime.asSeconds(), _player->getPosition());
		}
		else
		{
			delete _nests[i];
			_nests.erase(_nests.begin() + i);
			i--;
		}
	}
}
void Game::UpdateAbductors(sf::Time elapsedTime)
{
	for (int i = 0; i < _abductors.size(); i++)
	{
		if (_abductors[i]->getAlive())
		{
			Abductor::State state = _abductors[i]->getState();
			switch (state)
			{
				case Abductor::State::flock:
				{
					_abductors[i]->flock(_abductors, _player->getPosition());
					for (int j = 0; j < _astronauts.size(); j++)
					{
						_abductors[i]->findAstronaut(_astronauts[j]);
					}
					break;
				}
				case Abductor::State::seek:
				{
					_abductors[i]->seek();
					break;
				}
				default:
				{
					if (_abductors[i]->flee(_player->getPosition()))
					{
						_abductors[i]->getTarget()->Die();
						_abductors[i]->Die();

						Mutant* mutant = new Mutant(_bullets, _textureHolder.get(Textures::ID::Projectile_Interceptor));


						mutant->initialize(_abductors[i]->getPosition(), _textureHolder.get(Textures::ID::Mutant), _worldBounds);

						_mutants.push_back(mutant);
					}
					break;
				}
			}
			_abductors[i]->update(elapsedTime.asSeconds(), _player->getPosition());
		}
		else
		{
			delete _abductors[i];
			_abductors.erase(_abductors.begin() + i);
			i--;
		}
	}
}
void Game::UpdateMutants(sf::Time elapsedTime)
{
	bool once = true;
	int firstMutantInSwarm = -1;
	bool allCanFire = true;
	for (int i = 0; i < _mutants.size(); i++)
	{
		switch (_mutants[i]->getState())
		{
			case  Mutant::State::seek:
			{
				_mutants[i]->seek(_player->getPosition());
				
				break;
			}
			default:
			{
				if (once)
				{
					once = false;
					firstMutantInSwarm = i;
				}
				_mutants[i]->swarm(_mutants, _player->getPosition());
				if (!_mutants[i]->getCanFire())
				{
					allCanFire = false;
				}

				break;
			}
		}
		_mutants[i]->update(elapsedTime.asSeconds());
	}
	if (allCanFire && firstMutantInSwarm != -1)
	{
		sf::Vector2f fireDirection = _mutants[firstMutantInSwarm]->getFireDirection(_player->getPosition());
		for (int i = 0; i < _mutants.size(); i++)
		{
			_mutants[i]->Shoot(fireDirection);
		}
	}
}
void Game::UpdateAstronauts(sf::Time elapsedTime)
{
	for (int i = 0; i < _astronauts.size(); i++)
	{
		if (_astronauts[i]->getAlive())
		{
			_astronauts[i]->update(elapsedTime.asSeconds());
			
			int closestAlien;
			int closestDistance = 400;
			bool abductorsNearby = false;
			for (int j = 0; j < _abductors.size(); j++)
			{
				sf::Vector2f targetPos = sf::Vector2f(_abductors[j]->getPosition().x, _abductors[j]->getPosition().y);
				int d = Vector2Calculator::Distance(targetPos, _astronauts[i]->getPosition());
				if (d < 200)
				{
					abductorsNearby = true;
					if (d < closestDistance)
					{
						closestDistance = d;
						closestAlien = j;
					}
				}
			}
			if (!abductorsNearby)
			{
				if (_astronauts[i]->getIsRunning())
				{
					_astronauts[i]->setIsRunning(false);
					_astronauts[i]->setSpeed(_astronauts[i]->getSpeed() / 3.0f);
				}
			}
			else
			{
				if (!_astronauts[i]->getIsRunning())
				{
					_astronauts[i]->setIsRunning(true);
					_astronauts[i]->setSpeed(_astronauts[i]->getSpeed() * 3.0f);
					if (_astronauts[i]->getPosition().x > _abductors[closestAlien]->getPosition().x)
					{
						_astronauts[i]->setDirection(1);
					}
					else
					{
						_astronauts[i]->setDirection(-1);
					}
				}
			}
			
		}
		else
		{
			for (int j = 0; j < _abductors.size(); j++)
			{
				if (_abductors[j]->getTarget() == _astronauts[i])
				{
					_abductors[j]->setTarget(nullptr);
					_abductors[j]->setState(Abductor::State::flock);
				}
			}
			delete _astronauts[i];
			_astronauts.erase(_astronauts.begin() + i);
			i--;
		}
	}
}
#pragma endregion


void Game::NukeReleased()
{

}

void Game::render()
{
	_window.clear();	

	_window.setView(_worldView);

	for (int i = 0; i < _regions.size(); i++)
	{
		_window.draw(*_regions[i]);
	}

	DrawMeteors();
	
	DrawAlienNests();
	DrawAbductors();
	DrawMutants();
	DrawPowerUps();

	DrawProjectiles();
	DrawInterceptors();
	DrawBullet();


	_window.draw(*_player);
	DrawAstronauts();
	flock.draw(_window);
	_window.draw(_statisticsText);
	_window.display();
}

#pragma region Draw Methods

void Game::DrawProjectiles()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_window.draw(*_projectiles[i]);
	}
}
void Game::DrawInterceptors()
{
	for (int i = 0; i < _interceptors.size(); i++)
	{
		_window.draw(*_interceptors[i]);
	}
}
void Game::DrawBullet()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_window.draw(*_bullets[i]);
	}
}
void Game::DrawMeteors()
{
	for (int i = 0; i < _meteors.size(); i++)
	{
		_window.draw(*_meteors[i]);
	}
}
void Game::DrawPowerUps()
{
	for (int i = 0; i < _powerUps.size(); i++)
	{
		_window.draw(*_powerUps[i]);
	}
}
void Game::DrawAlienNests()
{
	for (int i = 0; i < _nests.size(); i++)
	{
		_window.draw(*_nests[i]);
	}
}
void Game::DrawAbductors()
{
	for (int i = 0; i < _abductors.size(); i++)
	{
		_window.draw(*_abductors[i]);
	}
}
void Game::DrawAstronauts()
{
	for (int i = 0; i < _astronauts.size(); i++)
	{
		_window.draw(*_astronauts[i]);
	}
}
void Game::DrawMutants()
{
	for (int i = 0; i < _mutants.size(); i++)
	{
		_window.draw(*_mutants[i]);
	}
}
#pragma endregion



void Game::updateStatistics(sf::Time elapsedTime)
{
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		_statisticsText.setString(
			"Frames / Second = " + toString(_statisticsNumFrames) + "\n" +
			"Time / Update = " + toString(_statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames) + "us\n" + 
			"Score = " + toString(_score));
		
		_statisticsUpdateTime -= sf::seconds(1.0f);
		_statisticsNumFrames = 0;
	}
}

void Game::handleInput()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		_window.close();
	}
}
