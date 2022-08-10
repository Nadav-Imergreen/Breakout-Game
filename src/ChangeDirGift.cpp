#include "ChangeDirGift.h"
#include "Paddle.h"

ChangeDirGift::ChangeDirGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::ChangeDir))
{
}

void ChangeDirGift::handleCollision(GameObject& otherobj)
{
}

void ChangeDirGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
