#include "Game.h"
#include "StringHelpers.h"


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
	: mWindow(sf::VideoMode(1280, 1024), "SFML Application", sf::Style::Close)
	, _textureHolder()
	, _player(new Player())
	, _alien1(new Alien())
	, _alien2(new Alien())
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	_textureHolder.load(Textures::Player1, "Media/Textures/Eagle.png");
	_textureHolder.load(Textures::Player2, "Media/Textures/Raptor.png");

	_player->initialize(sf::Vector2f(100, 100), _textureHolder.get(Textures::Player1), sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::W, mWindow.getSize());
	_alien1->initialize(sf::Vector2f(1000, 100), _textureHolder.get(Textures::Player2), mWindow.getSize(), true);
	_alien2->initialize(sf::Vector2f(1000, 800), _textureHolder.get(Textures::Player2), mWindow.getSize(), false);
	
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		handlePlayerInput();

		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	_player->update(elapsedTime.asSeconds());
	_alien1->update(elapsedTime.asSeconds(), _player->position());
	_alien2->update(elapsedTime.asSeconds(), _player->position());
}

void Game::render()
{
	mWindow.clear();	

	mWindow.draw(*_player);
	mWindow.draw(*_alien1);
	mWindow.draw(*_alien2);

	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput()
{	
	_player->readInput();
}
