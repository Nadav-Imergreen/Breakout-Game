#include "AddScoreGift.h"
#include "Paddle.h"

AddScoreGift::AddScoreGift(const sf::Vector2f& position, const sf::Vector2f& size)
	:Gift(position, size, &Resources::instance().getTexture(TextureType::AddScore))
{
}

void AddScoreGift::handleCollision(GameObject& otherobj)
{
}

void AddScoreGift::handleCollision(Paddle& paddle)
{
	m_deleted = true;
	paddle.handleCollision(*this);
}
