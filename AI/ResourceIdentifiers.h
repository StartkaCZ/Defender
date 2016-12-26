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
		Player,
		Abductor,
		AlienNest,
		Astronaut,
		Mutant,
		Obstacle_Meteor,
		PowerUp_SuperJump,
		Projectile_PlayerLazer,
		Projectile_Interceptor,

		Background,
		Foreground,
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
