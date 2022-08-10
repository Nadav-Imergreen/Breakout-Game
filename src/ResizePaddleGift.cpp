#include "ResizePaddleGift.h"
#include "Paddle.h"

ResizePaddleGift::ResizePaddleGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::IncreasePaddle))
{
}

void ResizePaddleGift::handleCollision(GameObject& otherobj)
{
}

void ResizePaddleGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
