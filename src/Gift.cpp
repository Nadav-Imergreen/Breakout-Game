#include "Gift.h"

Gift::Gift(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture)
	:StaticObject(position, size, texture)
{
}

void Gift::fall(sf::Time delta)
{
	m_sprite.move({ 0, delta.asSeconds() * GIFT_SPEED });
}

void Gift::setGiftBrickHit()
{
	m_giftBrickHit = true;
}

bool Gift::isBrickBroke() const
{
	return m_giftBrickHit;
}
