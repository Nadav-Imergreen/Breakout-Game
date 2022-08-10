#include "FastPaddleGift.h"
#include "Paddle.h"

FastPaddleGift::FastPaddleGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::FastPaddle))
{
}

void FastPaddleGift::handleCollision(GameObject& otherobj)
{
}

void FastPaddleGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
