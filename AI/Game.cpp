#include "Game.h"
#include "StringHelpers.h"

#include "ConstHolder.h"
#include "CollisionManager.h"
#include "ParticleSystemManager.h"
#include "AudioManager.h"

Game::Game()
	: _window(sf::VideoMode(1200, 900), "Defender", sf::Style::Close)
	, _worldView(_window.getDefaultView())
	, _worldBounds(0.f, 0.f, _worldView.getSize().x * SCREEN_TIME_SIZE, _worldView.getSize().y)
	, _textureHolder()
	, _player(nullptr)
	, _hud(nullptr)
	, _projectiles(std::vector<Projectile*>())
	, _interceptors(std::vector<Interceptor*>())
	, _bullets(std::vector<Bullet*>())
	, _meteors(std::vector<Meteor*>())
	, _powerUps(std::vector<PowerUp*>())
	, _nests(std::vector<AlienNest*>())
	, _abductors(std::vector<Abductor*>())
	, _mutants(std::vector<Mutant*>())
	, _astronauts(std::vector<Astronaut*>())
	, _regions(std::vector<Region*>())
	, _statisticsText()
	, _statisticsUpdateTime()
	, _statisticsNumFrames(0)
	, _score(0)
	, _state(State::Menu)
{
	loadContent();

	for (int i = 0; _regions.size() < SCREEN_TIME_SIZE; i++)
	{
		Region* region = new Region();

		region->Initialize(sf::Vector2f(i * _worldView.getSize().x, 0), _textureHolder.get(Textures::ID::Background), _textureHolder.get(Textures::ID::Foreground));

		_regions.push_back(region);
	}

	while (_mutants.size() < 6)
	{
		Mutant* mutant = new Mutant(_bullets, _textureHolder.get(Textures::ID::Projectile_Interceptor));

		float x = (rand() % (int)_worldBounds.width - 60) + 30;
		float y = (rand() % (int)_worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 60) + 30;

		mutant->initialize(sf::Vector2f(x,y), _textureHolder.get(Textures::ID::Mutant), _worldBounds);

		_mutants.push_back(mutant);

		SetupRegion(mutant);
	}

	while (_astronauts.size() < 5)
	{
		Astronaut* astronaut = new Astronaut();

		float x = rand() % (int)(_worldBounds.width - 256) + 128;
		float y = _worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 32;

		astronaut->Initialize(sf::Vector2f(x, y), _textureHolder.get(Textures::ID::Astronaut), _worldBounds);

		_astronauts.push_back(astronaut);

		SetupRegion(astronaut);
	}
	
	while (_meteors.size() < MAX_METEORS)
	{
		Meteor* meteor = new Meteor();

		meteor->Initialize(_textureHolder.get(Textures::ID::Obstacle_Meteor), _worldBounds);

		_meteors.push_back(meteor);

		SetupRegion(meteor);
	}
	
	PowerUp* powerUp = new PowerUp();
	powerUp->Initialize(_textureHolder.get(Textures::ID::PowerUp_SuperJump), ObjectType::PowerUp_SuperJump, _worldBounds);
	SetupRegion(powerUp);
	_powerUps.push_back(powerUp);

	powerUp = new PowerUp();
	powerUp->Initialize(_textureHolder.get(Textures::ID::PowerUp_Shield), ObjectType::PowerUp_Shield, _worldBounds);
	SetupRegion(powerUp);
	_powerUps.push_back(powerUp);

	powerUp = new PowerUp();
	powerUp->Initialize(_textureHolder.get(Textures::ID::PowerUp_RapidFire), ObjectType::PowerUp_RapidFire, _worldBounds);
	SetupRegion(powerUp);
	_powerUps.push_back(powerUp);
	
	while (_nests.size() < 1)
	{
		AlienNest* nest = new AlienNest(_interceptors, _abductors, _bullets, _textureHolder.get(Textures::ID::Projectile_Interceptor), _textureHolder.get(Textures::ID::Abductor), _textureHolder.get(Textures::ID::Projectile_Interceptor));

		float x = rand() % (int)(_worldBounds.width - 256) + 128;
		float y = rand() % (int)(_worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 256) + 128;

		nest->Initialize(sf::Vector2f(x, y), _textureHolder.get(Textures::ID::AlienNest), _worldBounds);

		SetupRegion(nest);

		_nests.push_back(nest);
	}
	
	_player = new Player(_projectiles, _textureHolder.get(Textures::ID::Projectile_PlayerLazer));
	_player->Initialize(sf::Vector2f(_worldBounds.width * 0.5f, _worldBounds.height * 0.5f), _textureHolder.get(Textures::ID::Player), _worldBounds);
	SetupRegion(_player);
	
	_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldBounds.height * 0.5f));

	_statisticsText.setFont(_fontHolder.get(Fonts::ID::Normal));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);


	AudioManager::Instance()->PlayMusic(AudioManager::MusicType::Menu);


	_state = State::Game;
	_level = 1;
	_hud = new HUD();
	_hud->Initialize(_textureHolder, _fontHolder.get(Fonts::ID::Normal), _level, _score, _player->getLives(), _astronauts.size(), _player);
	AudioManager::Instance()->PlayMusic(AudioManager::MusicType::Game);
}

void Game::loadContent()
{
	AudioManager::Instance()->LoadContent();

	_textureHolder.load(Textures::ID::Player, "Media/Textures/Player.png");
	_textureHolder.load(Textures::ID::Projectile_PlayerLazer, "Media/Textures/bullet.png");

	_textureHolder.load(Textures::ID::Astronaut, "Media/Textures/Astronaut.png");

	_textureHolder.load(Textures::ID::Abductor, "Media/Textures/Abductor.png");

	_textureHolder.load(Textures::ID::AlienNest, "Media/Textures/AlienNest.png");
	_textureHolder.load(Textures::ID::Projectile_Interceptor, "Media/Textures/Interceptor.png");

	_textureHolder.load(Textures::ID::Mutant, "Media/Textures/Mutant.png");

	_textureHolder.load(Textures::ID::Obstacle_Meteor, "Media/Textures/Meteor.png");

	_textureHolder.load(Textures::ID::PowerUp_SuperJump, "Media/Textures/SuperJumpPowerUp.png");
	_textureHolder.load(Textures::ID::PowerUp_Shield, "Media/Textures/ShieldPowerUp.png");
	_textureHolder.load(Textures::ID::PowerUp_RapidFire, "Media/Textures/RapidFirePowerUp.png");

	_textureHolder.load(Textures::ID::Background, "Media/Textures/Background.png");
	_textureHolder.load(Textures::ID::Foreground, "Media/Textures/Foreground.png");
	_textureHolder.load(Textures::ID::HUD, "Media/Textures/HUD.png");
	_textureHolder.load(Textures::ID::IconNuke, "Media/Textures/IconNuke.png");

	_textureHolder.load(Textures::ID::Particle_PlayerLazer, "Media/Textures/ParticlePlayerLazer.png");
	_textureHolder.load(Textures::ID::Particle_EnemyLazer, "Media/Textures/ParticleEnemyLazer.png");
	_textureHolder.load(Textures::ID::Particle_Death, "Media/Textures/ParticleDeath.png");
	_textureHolder.load(Textures::ID::Particle_PowerUp, "Media/Textures/ParticlePowerUp.png");
	_textureHolder.load(Textures::ID::Particle_PlayerTrail, "Media/Textures/ParticlePlayerTrail.png");

	_fontHolder.load(Fonts::ID::Normal, "Media/Sansation.ttf");

	ParticleSystemManager::Instance()->AddTexture(ParticleType::PlayerLazer, _textureHolder.get(Textures::ID::Particle_PlayerLazer));
	ParticleSystemManager::Instance()->AddTexture(ParticleType::EnemyLazer, _textureHolder.get(Textures::ID::Particle_EnemyLazer));
	ParticleSystemManager::Instance()->AddTexture(ParticleType::Death, _textureHolder.get(Textures::ID::Particle_Death));
	ParticleSystemManager::Instance()->AddTexture(ParticleType::PowerUp, _textureHolder.get(Textures::ID::Particle_PowerUp));
	ParticleSystemManager::Instance()->AddTexture(ParticleType::PlayerTrail, _textureHolder.get(Textures::ID::Particle_PlayerTrail));
}

void Game::SetupRegion(GameObject* gameObject)
{
	for (int i = 0; i < _regions.size(); i++)
	{
		if (_regions[i]->Contained(gameObject->getPosition()) == 0)
		{
			gameObject->SetRegion(i);
			_regions[gameObject->getRegion()]->AddGameObject(gameObject);
			gameObject->InsideRegion(true);
			break;
		}
	}
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
	switch (_state)
	{
	case Game::State::Menu:
		UpdateMenu(elapsedTime);
		break;
	case Game::State::Game:
		UpdateGame(elapsedTime);
		break;
	case Game::State::GameOver:
		UpdateGameOver(elapsedTime);
		break;

	default:
		break;
	}
}

void Game::UpdateMenu(sf::Time elapsedTime)
{

}
void Game::UpdateGame(sf::Time elapsedTime)
{
	//CollisionManager::Instance()->CheckForCollisions(_player, _projectiles, _interceptors, _powerUps, _meteors, _nests);
	CollisionManager::Instance()->CheckForCollisions(_regions);
	AudioManager::Instance()->Update(elapsedTime.asSeconds());
	ParticleSystemManager::Instance()->Update(elapsedTime.asSeconds());

	UpdatePlayer(elapsedTime);

	UpdateProjectiles(elapsedTime);
	UpdateInterceptors(elapsedTime);
	UpdateBullets(elapsedTime);

	UpdateMeteors(elapsedTime);

	UpdatePowerUps(elapsedTime);
	UpdateAlienNests(elapsedTime);
	UpdateAbductors(elapsedTime);
	UpdateMutants(elapsedTime);
	UpdateAstronauts(elapsedTime);

	UpdateCamera();

	_hud->Update(elapsedTime.asSeconds(), _score, _astronauts.size(), _abductors.size() + _nests.size() + _mutants.size(), _level, _worldView.getCenter() - _worldView.getSize()*0.5f);
}
void Game::UpdateGameOver(sf::Time elapsedTime)
{

}

#pragma region Update Game Methods

void Game::UpdatePlayer(sf::Time elapsedTime)
{
	_player->Update(elapsedTime.asSeconds());
	UpdateGameObjectBasedOnRegion(_player);
	if (_player->hasNuked())
	{
		NukeReleased();
		_player->NukingOver();
	}
}
void Game::UpdateProjectiles(sf::Time elapsedTime)
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		if (_projectiles[i]->getAlive())
		{
			_projectiles[i]->Update(elapsedTime.asSeconds());
			UpdateGameObjectBasedOnRegion(_projectiles[i]);

		}
		else
		{
			RemoveObjectFromRegion(_projectiles[i]);
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
			UpdateGameObjectBasedOnRegion(_interceptors[i]);
		}
		else
		{
			RemoveObjectFromRegion(_interceptors[i]);
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
			UpdateGameObjectBasedOnRegion(_bullets[i]);
		}
		else
		{
			RemoveObjectFromRegion(_bullets[i]);
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
			UpdateGameObjectBasedOnRegion(_meteors[i]);
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
			UpdateGameObjectBasedOnRegion(_powerUps[i]);
		}
		else
		{
			_score += POWER_UP_SCORE;
			RemoveObjectFromRegion(_powerUps[i]);
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
			_nests[i]->Update(elapsedTime.asSeconds(), _player->getPosition(), _meteors);
			UpdateGameObjectBasedOnRegion(_nests[i]);
		}
		else
		{
			_score += NEST_SCORE;
			RemoveObjectFromRegion(_nests[i]);
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
			_abductors[i]->update(elapsedTime.asSeconds(), _player->getPosition());
			UpdateGameObjectBasedOnRegion(_abductors[i]);

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
						SetupRegion(mutant);
					}
					break;
				}
			}
			_abductors[i]->update(elapsedTime.asSeconds(), _player->getPosition());
		}
		else
		{
			_score += ABDUCTOR_SCORE;
			RemoveObjectFromRegion(_abductors[i]);
			delete _abductors[i];
			_abductors.erase(_abductors.begin() + i);
			i--;
		}
	}
}

void Game::UpdateGameObjectBasedOnRegion(GameObject* gameObject)
{
	if (!gameObject->isInsideRegion())
	{
		_regions[gameObject->getRegion()]->AddGameObject(gameObject);
		gameObject->InsideRegion(true);
	}

	int contained = _regions[gameObject->getRegion()]->Contained(gameObject->getPosition());

	if (contained != 0)
	{
		_regions[gameObject->getRegion()]->RemoveGameObject(gameObject);
	}


	int teleport = gameObject->RegionCheck(contained);

	if (teleport == 1)
	{
		gameObject->TeleportLeft(_regions[_regions.size() - 1]->getPosition() + _regions[_regions.size() - 1]->getSize());
		_regions[gameObject->getRegion()]->AddGameObject(gameObject);
	}
	else if (teleport == -1)
	{
		gameObject->TeleportRight(_regions[_regions.size() - 1]->getPosition() + _regions[_regions.size() - 1]->getSize());
		_regions[gameObject->getRegion()]->AddGameObject(gameObject);
	}
	else if (contained != 0)
	{
		_regions[gameObject->getRegion()]->AddGameObject(gameObject);
	}
}

void Game::RemoveObjectFromRegion(GameObject* gameObject)
{
	_regions[gameObject->getRegion()]->RemoveGameObject(gameObject);
}

void Game::UpdateCamera()
{
	if (_player->getPosition().x < _regions[0]->getPosition().x + _regions[0]->getSize().x * 0.5f)
	{
		_worldView.setCenter(sf::Vector2f(_regions[0]->getPosition().x + _regions[0]->getSize().x * 0.5f, _worldView.getCenter().y));
	}
	else if (_player->getPosition().x > _regions[_regions.size() - 1]->getPosition().x + _regions[0]->getSize().x * 0.5f)
	{
		_worldView.setCenter(sf::Vector2f(_regions[_regions.size() - 1]->getPosition().x + _regions[0]->getSize().x * 0.5f, _worldView.getCenter().y));
	}
	else
	{
		_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldView.getCenter().y));
	}
}
void Game::UpdateMutants(sf::Time elapsedTime)
{
	bool once = true;
	int firstMutantInSwarm = -1;
	bool allCanFire = true;
	for (int i = 0; i < _mutants.size(); i++)
	{
		if (_mutants[i]->getAlive())
		{
			UpdateGameObjectBasedOnRegion(_mutants[i]);
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
		else
		{
			RemoveObjectFromRegion(_mutants[i]);
			delete _mutants[i];
			_mutants.erase(_mutants.begin() + i);
			i--;
		}
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
			UpdateGameObjectBasedOnRegion(_astronauts[i]);

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
			RemoveObjectFromRegion(_astronauts[i]);
			delete _astronauts[i];
			_astronauts.erase(_astronauts.begin() + i);
			i--;
		}
	}
}
#pragma endregion


void Game::NukeReleased()
{
	for (int i = 0; i < _nests.size(); i++)
	{
		ParticleSystemManager::Instance()->CreateParticleSystem(_nests[i]->getPosition(), ParticleType::Death);

		_score += NEST_SCORE;
		RemoveObjectFromRegion(_nests[i]);
		delete _nests[i];
		_nests.erase(_nests.begin() + i);
		i--;
	}

	for (int i = 0; i < _abductors.size(); i++)
	{
		ParticleSystemManager::Instance()->CreateParticleSystem(_abductors[i]->getPosition(), ParticleType::Death);

		_score += ABDUCTOR_SCORE;
		RemoveObjectFromRegion(_abductors[i]);
		delete _abductors[i];
		_abductors.erase(_abductors.begin() + i);
		i--;
	}

	for (int i = 0; i < _mutants.size(); i++)
	{
		ParticleSystemManager::Instance()->CreateParticleSystem(_mutants[i]->getPosition(), ParticleType::Death);

		_score += MUTANT_SCORE;
		RemoveObjectFromRegion(_mutants[i]);
		delete _mutants[i];
		_mutants.erase(_mutants.begin() + i);
		i--;
	}
}

void Game::render()
{
	_window.clear();	

	_window.setView(_worldView);

	switch (_state)
	{
	case Game::State::Menu:
		DrawMenu();
		break;
	case Game::State::Game:
		DrawGame();
		break;
	case Game::State::GameOver:
		DrawGameOver();
		break;

	default:
		break;
	}

	_window.draw(_statisticsText);
	_window.display();
}

void Game::DrawMenu()
{

}
void Game::DrawGame()
{
	DrawVisibleRegions();
	DrawVisibleObjects();

	ParticleSystemManager::Instance()->Draw(_window);
	_hud->Draw(_window);
	DrawRadar();
}
void Game::DrawGameOver()
{

}

#pragma region Draw Methods

void Game::DrawVisibleRegions()
{
	if (_player->getRegion() - 1 >= 0)
	{
		_regions[_player->getRegion() - 1]->DrawRegion(_window);
	}

	if (_player->getRegion() + 1 < _regions.size())
	{
		_regions[_player->getRegion() + 1]->DrawRegion(_window);
	}

	_regions[_player->getRegion()]->DrawRegion(_window);
}
void Game::DrawVisibleObjects()
{
	if (_player->getRegion() - 1 >= 0)
	{
		_regions[_player->getRegion() - 1]->DrawObjects(_window);
	}

	if (_player->getRegion() + 1 < _regions.size())
	{
		_regions[_player->getRegion() + 1]->DrawObjects(_window);
	}

	_regions[_player->getRegion()]->DrawObjects(_window);
}

void Game::DrawRadar()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		DrawRectangle(_projectiles[i]->getSize(), _projectiles[i]->getPosition(), sf::Color::Yellow);
	}

	for (int i = 0; i < _interceptors.size(); i++)
	{
		DrawRectangle(_interceptors[i]->getSize(), _interceptors[i]->getPosition(), sf::Color::Yellow);
	}

	for (int i = 0; i < _meteors.size(); i++)
	{
		DrawRectangle(_meteors[i]->getSize(), _meteors[i]->getPosition(), sf::Color(100, 100, 100, 255));
	}

	for (int i = 0; i < _powerUps.size(); i++)
	{
		DrawRectangle(_powerUps[i]->getSize(), _powerUps[i]->getPosition(), sf::Color::Blue);
	}

	for (int i = 0; i < _nests.size(); i++)
	{
		DrawRectangle(_nests[i]->getSize(), _nests[i]->getPosition(), sf::Color::Red);
	}

	for (int i = 0; i < _abductors.size(); i++)
	{
		DrawRectangle(_abductors[i]->getSize(), _abductors[i]->getPosition(), sf::Color::Red);
	}

	for (int i = 0; i < _astronauts.size(); i++)
	{
		DrawRectangle(_astronauts[i]->getSize(), _astronauts[i]->getPosition(), sf::Color::Cyan);
	}

	for (int i = 0; i < _mutants.size(); i++)
	{
		DrawRectangle(_mutants[i]->getSize(), _mutants[i]->getPosition(), sf::Color::Red);
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		DrawRectangle(_bullets[i]->getSize(), _bullets[i]->getPosition(), sf::Color::Yellow);
	}

	DrawRectangle(_player->getSize(), _player->getPosition(), sf::Color::Green);
	DrawCameraRectangle();
}
void Game::DrawRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour)
{
	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(size.x * SIZE_SCALAR, size.y * SIZE_SCALAR));
	
	float hightNotUsed = HUD_HEIGHT + (_worldBounds.height * (1 - PLAYER_OFFSET_FROM_GROUND));

	rectangle.setPosition(sf::Vector2f((position.x / _worldBounds.width) * _worldView.getSize().x + _worldView.getCenter().x - _worldView.getSize().x * 0.5f, ((position.y - HUD_HEIGHT) / (_worldBounds.height - hightNotUsed)) * RADAR_HIGHT));
	rectangle.setOrigin(rectangle.getSize() *0.5f);
	
	rectangle.setFillColor(colour);

	_window.draw(rectangle);
}
void Game::DrawCameraRectangle()
{
	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(((_worldView.getSize().x / _worldBounds.width) * _worldView.getSize().x) - RADAR_CAMERA_RECTANGLE, ((_worldView.getSize().y / (_worldBounds.height - HUD_HEIGHT)) * RADAR_HIGHT) - RADAR_CAMERA_RECTANGLE));

	float hightNotUsed = _worldBounds.height * (1 - PLAYER_OFFSET_FROM_GROUND);

	rectangle.setPosition(sf::Vector2f((_worldView.getCenter().x / _worldBounds.width) * _worldView.getSize().x + _worldView.getCenter().x - _worldView.getSize().x * 0.5f, ((_worldView.getCenter().y - HUD_HEIGHT) / (_worldBounds.height - hightNotUsed)) * RADAR_HIGHT + RADAR_CAMERA_RECTANGLE));
	rectangle.setOrigin(rectangle.getSize() *0.5f);

	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2.5f);

	rectangle.setFillColor(sf::Color::Transparent);

	_window.draw(rectangle);
}

#pragma endregion

void Game::Destroy()
{
	delete _player;

	while (true)
	{
		delete _projectiles[0];
	}
	_projectiles.clear();

	while (true)
	{
		delete _interceptors[0];
	}
	_interceptors.clear();

	while (true)
	{
		delete _meteors[0];
	}
	_meteors.clear();

	while (true)
	{
		delete _powerUps[0];
	}
	_powerUps.clear();

	while (true)
	{
		delete _nests[0];
	}
	_nests.clear();

	while (true)
	{
		delete _abductors[0];
	}
	_abductors.clear();

	while (true)
	{
		delete _mutants[0];
	}
	_mutants.clear();

	while (true)
	{
		delete _astronauts[0];
	}
	_astronauts.clear();

	while (true)
	{
		delete _regions[0];
	}
	_regions.clear();

	delete _hud;
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		_statisticsText.setString(
			"Frames / Second = " + toString(_statisticsNumFrames) + "\n" +
			"Time / Update = " + toString(_statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames) + "us\n");
		
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
