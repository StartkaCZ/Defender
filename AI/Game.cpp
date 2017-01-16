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
	, _meteors(std::vector<Meteor*>())
	, _powerUps(std::vector<PowerUp*>())
	, _nests(std::vector<AlienNest*>())
	, _abductors(std::vector<Abductor*>())
	, _regions(std::vector<Region*>())
	, _statisticsText()
	, _statisticsUpdateTime()
	, _statisticsNumFrames(0)
	, _score(0)
{
	loadContent();

	for (int i = 0; _regions.size() < SCREEN_TIME_SIZE; i++)
	{
		Region* region = new Region();

		region->Initialize(sf::Vector2f(i * _worldView.getSize().x, 0), _textureHolder.get(Textures::ID::Background), _textureHolder.get(Textures::ID::Foreground));

		_regions.push_back(region);
	}

	
	while (_meteors.size() < MAX_METEORS)
	{
		Meteor* meteor = new Meteor();

		meteor->Initialize(_textureHolder.get(Textures::ID::Obstacle_Meteor), _worldBounds);

		_meteors.push_back(meteor);

		SetupRegion(meteor);
	}
	/*
	while (_powerUps.size() < MAX_POWER_UPS)
	{
		PowerUp* powerUp = new PowerUp();

		powerUp->Initialize(_textureHolder.get(Textures::ID::PowerUp_SuperJump), ObjectType::PowerUp_SuperJump, _worldBounds);

		_powerUps.push_back(powerUp);
	}
	*/
	while (_nests.size() < 1)
	{
		AlienNest* nest = new AlienNest(_interceptors, _abductors, _textureHolder.get(Textures::ID::Projectile_Interceptor), _textureHolder.get(Textures::ID::Abductor));

		float x = (rand() % (int)_worldBounds.width - 256) + 128;
		float y = (rand() % (int)_worldBounds.height * PLAYER_OFFSET_FROM_GROUND - 256) + 128;

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

void Game::SetupRegion(GameObject* gameObject)
{
	for (int i = 0; i < _regions.size(); i++)
	{
		if (_regions[i]->Contained(gameObject->getPosition()) == 0)
		{
			gameObject->SetRegion(i);
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
	CollisionManager::Instance()->CheckForCollisions(_player, _projectiles, _interceptors, _powerUps, _meteors, _nests);

	_player->Update(elapsedTime.asSeconds());
	UpdateGameObjectBasedOnRegion(_player);
	if (_player->hasNuked())
	{
		NukeReleased();
		_player->NukingOver();
	}

	_score++;

	UpdateProjectiles(elapsedTime);
	UpdateInterceptors(elapsedTime);
	UpdateMeteors(elapsedTime);

	UpdatePowerUps(elapsedTime);
	UpdateAlienNests(elapsedTime);
	UpdateAbductors(elapsedTime);

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

#pragma region UpdateMethods

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
			delete _interceptors[i];
			_interceptors.erase(_interceptors.begin() + i);
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
			UpdateGameObjectBasedOnRegion(_nests[i]);
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
		/*if (_abductors[i]->getAlive())
		{
		_abductors[i]->Update(elapsedTime.asSeconds());
		}
		else
		{
		delete _abductors[i];
		_abductors.erase(_abductors.begin() + i);
		i--;
		}*/
	}
}

void Game::UpdateGameObjectBasedOnRegion(GameObject* gameObject)
{
	int contained = _regions[gameObject->getRegion()]->Contained(gameObject->getPosition());

	if (contained != 0)
	{
		_regions[gameObject->getRegion()]->RemoveGameObject(gameObject);
	}


	int teleport = gameObject->RegionCheck(contained);

	if (teleport == 1)
	{
		gameObject->TeleportLeft(_regions[_regions.size() - 1]->getPosition() + _regions[_regions.size() - 1]->getSize());
	}
	else if (teleport == -1)
	{
		gameObject->TeleportRight(_regions[_regions.size() - 1]->getPosition() + _regions[_regions.size() - 1]->getSize());
	}


	_regions[gameObject->getRegion()]->AddGameObject(gameObject);
}

void Game::RemoveObjectFromRegion(GameObject* gameObject)
{
	_regions[gameObject->getRegion()]->RemoveGameObject(gameObject);
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

	DrawPowerUps();

	DrawProjectiles();
	DrawInterceptors();

	_window.draw(*_player);

	DrawRadar();

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

	DrawRectangle(_player->getSize(), _player->getPosition(), sf::Color::Green);
	DrawCameraRectangle();
}

void Game::DrawRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour)
{
	const float RADAR_HIGHT = 150.0f;
	const float SIZE_SCALAR = 0.20f;

	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(size.x * SIZE_SCALAR, size.y * SIZE_SCALAR));
	rectangle.setPosition(sf::Vector2f((position.x / _worldBounds.width) * _worldView.getSize().x + _worldView.getCenter().x - _worldView.getSize().x * 0.5f, (position.y / _worldBounds.height) * RADAR_HIGHT));
	rectangle.setOrigin(rectangle.getSize() *0.5f);
	rectangle.setFillColor(colour);

	_window.draw(rectangle);
}

void Game::DrawCameraRectangle()
{
	const float RADAR_HIGHT = 150.0f;
	const float CAMERA_RECTANGLE = 2.5f + 2.5f;

	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(((_worldView.getSize().x / _worldBounds.width) * _worldView.getSize().x) - CAMERA_RECTANGLE, ((_worldView.getSize().y / _worldBounds.height) * RADAR_HIGHT) - CAMERA_RECTANGLE));

	rectangle.setPosition(sf::Vector2f((_worldView.getCenter().x / _worldBounds.width) * _worldView.getSize().x + _worldView.getCenter().x - _worldView.getSize().x * 0.5f, (_worldView.getCenter().y / _worldBounds.height) * RADAR_HIGHT));
	rectangle.setOrigin(rectangle.getSize() *0.5f);

	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2.5f);

	rectangle.setFillColor(sf::Color::Transparent);

	_window.draw(rectangle);
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
