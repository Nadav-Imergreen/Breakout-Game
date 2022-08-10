#include "GiftBrick.h"

GiftBrick::GiftBrick(const sf::Vector2f& position, const sf::Vector2f& size)
	:Brick(position, size, &Resources::instance().getTexture(TextureType::GiftBrick), 1)
{
}
