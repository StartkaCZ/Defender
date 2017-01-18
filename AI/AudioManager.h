#pragma once

#include "SFML\Audio.hpp"

#include <queue>


class AudioManager
{
public:
	enum class SoundType
	{
		UnitHit,
		UnitDestroyed,
		PowerUpCollected,
		Nuked,
		SuperJump,
		ShotFired,
	};

	enum class MusicType
	{
		Game,
		Menu
	};

public:
							AudioManager();
							~AudioManager();

	static AudioManager*	Instance();

	void					LoadContent();
	void					Update(float dt);

	void					PlaySound(SoundType type);
	void					PlayMusic(MusicType type);
		
	void					CanPlayMusic(bool canPlay);
	void					CanPlaySound(bool canPlay);

private:	
	void					AddSoundEffect(sf::SoundBuffer& buffer);

private:
	static AudioManager*	_instance;

	sf::SoundBuffer			_unitHitSoundBuffer;
	sf::SoundBuffer			_unitDestroyedSoundBuffer;
	sf::SoundBuffer			_powerUpCollectedSoundBuffer;
	sf::SoundBuffer			_nukedSoundBuffer;
	sf::SoundBuffer			_superJumpSoundBuffer;
	sf::SoundBuffer			_shotFiredSoundBuffer;

	sf::Music				_gameMusic;
	sf::Music				_menuMusic;

	std::queue<sf::Sound>	_playingSounds;

	bool					_canPlayMusic;
	bool					_canPlaySounds;
};

