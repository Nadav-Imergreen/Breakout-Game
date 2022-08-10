#include "StrongBallGift.h"
#include "Paddle.h"

StrongBallGift::StrongBallGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::StrongBall))
{
}

void StrongBallGift::handleCollision(GameObject& otherobj)
{
}

void StrongBallGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
