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
	, _meteors(std::vector<Meteor*>())
	, _powerUps(std::vector<PowerUp*>())
	, _statisticsText()
	, _statisticsUpdateTime()
	, _statisticsNumFrames(0)
	, _score(0)
{
	loadContent();

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

	_player = new Player(_projectiles);
	_player->Initialize(sf::Vector2f(_worldBounds.width * 0.5f, _worldBounds.height * 0.5f), _textureHolder.get(Textures::ID::Player), _textureHolder.get(Textures::ID::Projectile_PlayerLazer), _worldBounds);
	_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldBounds.height * 0.5f));

	_statisticsText.setFont(_fontHolder.get(Fonts::ID::Normal));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
}

void Game::loadContent()
{
	_textureHolder.load(Textures::ID::Player, "Media/Textures/Eagle.png");
	_textureHolder.load(Textures::ID::Projectile_PlayerLazer, "Media/Textures/Eagle.png");
	_textureHolder.load(Textures::ID::PowerUp_SuperJump, "Media/Textures/Eagle.png");

	_textureHolder.load(Textures::ID::Abdusctor, "Media/Textures/Raptor.png");
	_textureHolder.load(Textures::ID::Obstacle_Meteor, "Media/Textures/Raptor.png");

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
	CollisionManager::Instance()->CheckForCollisions(_player, _projectiles, _powerUps, _meteors);

	_player->Update(elapsedTime.asSeconds());
	if (_player->hasNuked())
	{
		NukeReleased();
		_player->NukingOver();
	}

	_score++;

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

	_worldView.setCenter(sf::Vector2f(_player->getPosition().x, _worldView.getCenter().y));
}

void Game::NukeReleased()
{

}

void Game::render()
{
	_window.clear();	

	_window.setView(_worldView);


	for (int i = 0; i < _meteors.size(); i++)
	{
		_window.draw(*_meteors[i]);
	}

	for (int i = 0; i < _projectiles.size(); i++)
	{
		_window.draw(*_projectiles[i]);
	}

	for (int i = 0; i < _powerUps.size(); i++)
	{
		_window.draw(*_powerUps[i]);
	}

	_window.draw(*_player);

	_window.draw(_statisticsText);
	_window.display();
}

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
