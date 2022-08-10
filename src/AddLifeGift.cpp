#include "AddLifeGift.h"
#include "paddle.h"

AddLifeGift::AddLifeGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::AddLife))
{
}

void AddLifeGift::handleCollision(GameObject& otherobj)
{
}

void AddLifeGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
