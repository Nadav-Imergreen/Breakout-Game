#include "Brick.h"
#include "Ball.h"

Brick::Brick(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, int maxCounter)
	:StaticObject(position, size, texture), m_maxHitCounter(maxCounter)
{
}

void Brick::handleCollision(GameObject& otherobj)
{
	otherobj.handleCollision(*this);
}

void Brick::handleCollision(Ball& ball)
{
	if (isMaxHits())
		m_deleted = true;
	else       
	{	// for a double hit brick - change brick texture to a cracked brick after 1 hit and encrees hit counter
		m_sprite.setTexture(Resources::instance().getTexture(TextureType::DamageBrick));
		m_hitCounter++;
	}

}

bool Brick::isDamaged() const
{
	return m_damaged;
}

bool Brick::isMaxHits() const
{
	return m_hitCounter == m_maxHitCounter;
}

