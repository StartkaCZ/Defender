#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum class ID
	{
		//GameObjects
		Player,
		Abductor,
		AlienNest,
		Astronaut,
		Mutant,
		Obstacle_Meteor,
		PowerUp_SuperJump,
		PowerUp_Shield,
		PowerUp_RapidFire,
		Projectile_PlayerLazer,
		Projectile_Interceptor,

		//Background
		Background,
		Foreground,

		//HUD
		HUD,

		//Particles
		Particle_PlayerLazer,
		Particle_EnemyLazer,
		Particle_Death,
		Particle_PowerUp,
	};
}

namespace Fonts
{
	enum class ID
	{
		Normal,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_H
