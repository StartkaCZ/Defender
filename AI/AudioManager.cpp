#include "AudioManager.h"

AudioManager* AudioManager::_instance = nullptr;

AudioManager::AudioManager()
	: _playingSounds(std::queue<sf::Sound>())
	, _canPlayMusic(false)
	, _canPlaySounds(false)
{
	
}


AudioManager::~AudioManager()
{
	if (_instance)
	{
		delete _instance;
	}
}

AudioManager* AudioManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new AudioManager();
	}

	return _instance;
}
			  
void AudioManager::LoadContent()
{
	_unitHitSoundBuffer.loadFromFile("Media/Audio/Yay.wav");
	__unitDestroyedSoundBuffer.loadFromFile("Media/Audio/Yay.wav");
	_powerUpCollectedSoundBuffer.loadFromFile("Media/Audio/Yay.wav");
	_nukedSoundBuffer.loadFromFile("Media/Audio/Yay.wav");
	_superJumpSoundBuffer.loadFromFile("Media/Audio/Yay.wav");
	_shotFiredSoundBuffer.loadFromFile("Media/Audio/Yay.wav");

	_gameMusic.openFromFile("Media/Audio/Yay.ogg");
	_menuMusic.openFromFile("Media/Audio/Yay.ogg");
}

void AudioManager::Update(float dt)
{
	if (!_playingSounds.empty())
	{
		if (_playingSounds.front().getStatus() == sf::Sound::Stopped)
		{
			_playingSounds.pop();
		}
	}
}

	   
void AudioManager::PlaySound(SoundType type)
{
	if (_canPlaySounds)
	{
		switch (type)
		{
		case AudioManager::SoundType::UnitHit:
			AddSoundEffect(_unitHitSoundBuffer);
			break;

		case AudioManager::SoundType::UnitDestroyed:
			AddSoundEffect(__unitDestroyedSoundBuffer);
			break;

		case AudioManager::SoundType::PowerUpCollected:
			AddSoundEffect(_powerUpCollectedSoundBuffer);
			break;

		case AudioManager::SoundType::Nuked:
			AddSoundEffect(_nukedSoundBuffer);
			break;

		case AudioManager::SoundType::SuperJump:
			AddSoundEffect(_superJumpSoundBuffer);
			break;

		case AudioManager::SoundType::ShotFired:
			AddSoundEffect(_shotFiredSoundBuffer);
			break;

		default:
			break;
		}
	}
}

void AudioManager::AddSoundEffect(sf::SoundBuffer& buffer)
{
	sf::Sound sound = sf::Sound();
	sound.setBuffer(buffer);

	_playingSounds.push(sound);
	_playingSounds.back().play();
}

void AudioManager::PlayMusic(MusicType type)
{
	if (_canPlayMusic)
	{
		switch (type)
		{
		case AudioManager::MusicType::Game:
			_menuMusic.stop();

			_gameMusic.play();
			_gameMusic.setLoop(true);
			break;

		case AudioManager::MusicType::Menu:
			_gameMusic.stop();

			_menuMusic.play();
			_menuMusic.setLoop(true);
			break;

		default:
			break;
		}
	}
}
	   
void AudioManager::CanPlayMusic(bool canPlay)
{
	_canPlayMusic = canPlay;
}
void AudioManager::CanPlaySound(bool canPlay)
{
	_canPlaySounds = canPlay;
}
