#pragma once

#include <SFML/Graphics.hpp>

class Region : public sf::Drawable, protected sf::NonCopyable
{
public:
					Region();
					~Region();

	void			Initialize(sf::Vector2f position, sf::Texture& backgroundTexture, sf::Texture& foregroundTexture);

protected:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite		_backgroundTexture;
	sf::Sprite		_foregroundTexture;
};

